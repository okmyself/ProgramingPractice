##Kotlin基础语法教程（二）

[TOC]

###面向对象编程

####类的声明

Kotlin中类声明的格式为：
```
class 类名 {
    声明类的成员
}
```
其中类的成员包括初始化代码块、构造函数(方法)、属性、成员函数、内部类和嵌套类等。

在程序中创建一个类的实例时，只需要像调用函数一样，不需要Java中的`new`关键字。

####属性

在Java中经常通过私有化成员变量，提供`getter`、`setter`访问器实现对成员变量的访问的方法对成员变量进行封装，这样做能够提高代码的复用性和安全性。

Kotlin中的成员属性则是对支持字段(也叫幕后字段)的封装：属性本身并不存储数据，而是存储在属性的支持字段中。Kotlin语言默认会对支持字段进行封装，以提高代码的复用性。支持字段由编译器自动添加，不允许我们手动添加。

*注：*
可以通过注解`@JvmField`修饰一个成员属性直接暴露其支持字段，但会破坏其封装性，通常在Kotlin与Java的互操作中使用这些关键字。

#####`getter`和`setter`访问器

Kotlin中声明属性的语法是：
```
    val/var 属性名[: 数据类型] [= 属性初始值]
        [getter访问器]
        [setter访问器]
```
其中`[]`中的内容为可以省略。使用`val`声明的属性为只读属性，只能有`getter`访问器，当不提供`getter`和`setter`访问器时，Kotlin会为其生成默认的访问器，直接对支持字段赋值或返回支持字段的值。Kotlin的属性分为顶层属性和成员属性，顶层属性在类之外声明，也就是全局变量。

```
fun main(args: Array<String>) {
    val a = Person()
    a.name = "Tom.Cruise"
    println(a.firstName)
    println(a.lastName)
}

class Person {
    var firstName: String = "John"
        get() = field
        set(value) { field = value }
    var lastName: String = "Smith"
    var name: String
        set(value) {
            val namePart = value.split(".")     //通过.把文本分割到两个成员的数组
            if (namePart.size != 2) {           //过滤数据，体现封装性
                println("不正确的姓名格式")
                return
            }
            firstName = namePart[0]
            lastName = namePart[1]
        }
        get() {
            return "$firstName.$lastName"
        }
        //也可以写成表达式函数体形式：get() = "$firstName.$lastName"
        val nameHash get() = name.hashCode()
}
```
`Person`类的属性`firstName`手动设置了`getter`和`setter`访问器，在访问器语句块中，通过隐式标识符`field`访问支持字段，对支持字段进行赋值和读取操作。

上述代码中`Person`类的属性`lastName`没有设置`getter`和`setter`访问器，由于它是`var`可变变量，编译器会为它们生成默认的访问器，直接对支持字段赋值或返回支持字段的值。

并不是所有的属性都会有支持字段，如`name`属性的值是保存在`firstName`和`lastName`中的，一般称之为计算属性。还有一些只读属性，如`nameHash`，它并没有初始化，这个属性在编译后就会消失，只留下一个`getNameHash()`函数。值得注意的是，Kotlin的属性定义为非空类型时，如果不提供所需的全部访问器，就必须进行初始化(编译器自动生成相应的默认访问器)。

#####延迟初始化属性

在编程中可能会遇到在运行时才需要初始化或是初始化之后可以确定不为`null`的成员变量，通过用`lateinit`修饰属性，可以允许变量在调用前进行初始化(延迟初始化属性可以被初始化多次)，若不初始化就直接调用，会抛出`UninitializedPropertyAccessException`异常。

```
fun main(args: Array<String>) {
    val a = Student()
    a.name = "Tom.Cruise"
    a.school = School()     //初始化school属性，否则下两句代码均会抛出kotlin.UninitializedPropertyAccessException异常
    a.school.name = "abc"
    println(a.school.name)
}

class Student {
    var firstName: String = "John"
    var lastName: String = "Smith"
    var name: String
        set(value) {
            val namePart = value.split(".")
            firstName = namePart.getOrNull(0) ?: ""
            lastName = namePart.getOrNull(1) ?: ""
        }
        get() = "$firstName.$lastName"
    lateinit var school: School
}

class School {
    var name: String = ""
}
```

`lateinit`关键字只能修饰`var`声明的变量，并且不能是可空类型(类型后加`?`)，也不能是基本数据类型。

#####委托属性

委托属性使用`by`关键字进行声明，其格式是`val/var 属性名: 属性类型 by 表达式`，用于将属性委托给委托对象，委托对象不需要继承什么特别的接口，只需要拥有`operator`关键字(运算符重载关键字，后面后会讲到)修饰的`setValue()`(仅用`var`声明的变量需要)和`getValue()`函数即可，其参数请见下面的代码：

```
import kotlin.reflect.KProperty

fun main(args: Array<String>) {
    val a = Example()
    a.p = "abc"
    println(a.p)
}

class Example {
    var p: String by Delegate()
}

class Delegate {
    operator fun getValue(thisRef: Any?, property: KProperty<*>): String {
        return "将${thisRef}实例中的'${property.name}'属性委托给此类。"
    }
    operator fun setValue(thisRef: Any?, property: KProperty<*>, value: String) {
        println("${value}被赋值给${thisRef}实例中的'${property.name}'属性。")
    }
}
```

其中参数中的`thisRef`是属性的拥有者对象的引用，`property`是对属性的描述，它是`KProperty<*>`类型或是它的父类，`value`是调用`setter`访问器时传递进来的属性的值。

Kotlin官方在标准库里提供了委托属性的三个常用场景作为委托属性的范例，这里展示四种委托的用法：

- 懒加载属性：懒加载属性与延迟初始化属性比较类似，它是通过`val 属性名: 属性类型 by lazy { ... }`，属性类型必须与`lazy()`函数第一个参数(该参数是函数类型，一般使用Lambda表达式)的返回值一致。

```
fun main(args: Array<String>) {
    val a = Student()
    a.firstName = "Bill"
    println(a.name)
    a.firstName = "Mike"
    println(a.name)     //两次输出结果相同
}

class Student {
    var firstName: String = "John"
    var lastName: String = "Smith"
    val name: String by lazy { firstName + "." +lastName }
}
```

- 非空属性：前面提到延迟初始化属性不能用于基本类型变量，我们可以将不可空`var`声明的变量委托给`Delegates.notNull()`函数来代替这一功能，此时不必赋初值，但在第一次调用数据前必须进行赋值操作，否则运行时会抛出`IllegalStateException`异常，如：
```
    var a: Int by Delegates.notNull()
    println(a)      //运行时抛出IllegalStateException异常
    a = 1
    println(a)
```

懒加载属性只能用于`val`修饰的只读变量，被委托的属性将在第一次调用时被初始化，此后属性值不再改变。

- 可观察属性：可观察属性用于监听属性的变化，当属性变化时会触发委托对象，通过将属性委托给`Delegates.observable()`对象声明可观察属性。

```
import kotlin.properties.Delegates

fun main(args: Array<String>) {
    val a = Student()
    a.studentName = "Mike.Smith"
}

class Student {
    var studentName: String by Delegates.observable("noname") {
        //Lambda表达式的三个参数分别是属性对象，修改前的值，修改后的值
        property, oldValue, newValue ->
        println("${property.name}属性的内容从${oldValue}改变到${newValue}")
    }
}
```

- 可否决属性：如果想拦截属性的修改，可以使用`Delegates.vetoable()`函数。与可观察属性类似，该函数接收两个参数，第一个是初始值，第二个是属性被改变前调用的函数，与可观察属性不同的是第二个参数需要提供布尔型返回值(一般是Lambda表达式的最后一行语句)，如果函数返回false，则属性不会被修改。


#####扩展属性

在一些情况下，Kotlin可以很方便的扩展一个类的函数(将在下一节提到)和属性，而不需要继承或者使用类似Java中的装饰器模式(Decorator)。

```
fun main(args: Array<String>) {
    val a = Student()
    println(a.name)
    a.name = "Tom.Cruise"   //调用扩展属性的set方法
    
    println(a.firstName)    //调用扩展属性的get方法
    println(a.lastName)
    println((-1).abs)
}

class Student {
    var firstName: String = "John"
    var lastName: String = "Smith"
}
//扩展属性
var Student.name: String
    get() = "$firstName.$lastName"
    set(value) {
        val namePart = value.split(".")
        if (namePart.size != 2) return
        firstName = namePart[0]
        lastName = namePart[1]
    }
//扩展基本类型对应包装类的属性
val Int.abs: Int
    get() = if(this < 0) -this else this
```

上面的代码对`Student`类扩展了一个`name`属性，对基本数据类型`Int`扩展了一个`abs`属性，调用方式与普通属性基本相同。Kotlin中的扩展属性不存在支持字段，必须提供`getter`访问器，如果是`var`声明的变量，还需要提供`setter`访问器。

####函数

#####扩展函数

扩展函数的定义与扩展属性类似，可以对任意一个类型进行扩展，示例代码如下：
```
fun main(args: Array<String>) {
    println(2.square())
    println(Student().toString())
}

class Student {
    var firstName: String = "John"
    var lastName: String = "Smith"
    var gender: Boolean = true
    var age: Int = 18
}
//扩展函数
fun Student.toString(): String {
    return """姓名：${firstName + "." + lastName}
        |年龄：$age
        |性别：${if (gender) "男" else "女"}
    """.trimMargin()
}
//扩展基本数据类型的函数
fun Int.square(): Int {
    return this * this
}
```
上述代码中的扩展函数`toString()`并没有成功执行，原因是`Student`类中继承了父类`Any`(类似于Java中的`Object`类，但只有`equals()`、`toString()`、`hashCode()`三个函数)中的`toString()`函数，在扩展函数或属性与成员函数或属性相冲突时，始终时调用成员函数或属性。

#####构造函数

Kotlin的构造函数有主、次之分，与Java中使用与类名同名且没有返回值的方法不同，Kotlin的构造函数使用关键字`constructor`声明，其中主构造函数最多可以有一个(可以没有)，次构造函数可以有任意多个(可以没有)。

- 主构造函数：主构造函数是声明在类名后的构造函数，在类名后使用`constructor(参数列表)`的形式进行声明，主构造函数里面不能包含任何代码，进行初始化的代码可以写在初始化代码块`init`中，示例代码如下：

```
fun main(args: Array<String>) {
    val John = Person("John", "Smith", 18)
}
//创建带有一个主构造函数的类
class Person constructor(firstName: String, lastName: String, age: Int) {
    val name: String
    var age: Int
    init {
        name = "$firstName.$lastName"
        this.age = age
    }
}
```

上述代码第2行中创建了一个`Person`对象，创建对象时不需要使用Java中的`new`关键字，直接像调用函数一样创建类即可。当成员属性和构造函数(包括主构造函数和后面提到的次构造函数)的参数名相冲突时，使用`this.属性名`访问成员属性。上述代码初始化块中对成员属性的初始化可以写在属性初始化器中，其等价代码如下：
```
class Person constructor(firstName: String, lastName: String, age: Int) {
    val name: String = "$firstName.$lastName"
    var age: Int = age
}
```

为了使代码更加简洁，Kotlin允许将`var`或`val`声明的成员属性写在主构造函数的参数列表中，并且当主构造函数的`constructor`关键字没有注解和可见性修饰符修饰时，可以省略主构造函数中的该关键字，即：
```
class Person(firstName: String, lastName: String, var age: Int) {
    val name: String = "$firstName.$lastName"
}
```
这种情况下Kotlin编译器会自动为其生成相应的属性，但在参数中使用`var`或`val`声明参数仅能用于主构造函数，不能用于次构造函数。

- 次构造函数：声明在类体中的构造函数称为次构造函数，构造函数之间是重载关系。当主构造函数存在时，次构造函数必须直接或间接的委托给主构造函数，并且初始化代码块(`init`)会在次构造函数代码块之前执行。

次构造函数调用主构造函数或者其他次构造函数的方法是在参数列表后面使用冒号，然后加上`this(参数列表)`调用相应的构造函数。
```
fun main(args: Array<String>) {
    val John = Person("John", "Smith")
}
//创建带有一个主构造函数和一个次构造函数的类
class Person(val name: String, var age: Int) {
    init { println("主构造函数被调用") }
    constructor(firstName: String, lastName: String, age: Int) : this("$firstName.$lastName", age)
    constructor(name: String) : this(name, 18)  //构造函数可以没有函数体
    constructor(firstName: String, lastName: String) : this(firstName, lastName, 18) {
        println("次构造函数被调用")
    }
}
```

*注：*
1. 当主构造函数中的所有参数均使用参数默认值或类中不包含任何构造函数(包括主构造函数和次构造函数)时，编译器会为其生成一个无参数的默认构造函数，它是主构造函数。
2. `init`代码块可以存在于没有主构造函数的类中，它将在次构造函数之前执行。

####可见性修饰符


Kotlin语言的可见性修饰符与Java有很大不同，可见性修饰符修饰顶层成员(顶层类、顶层函数、全局变量、`object`对象、接口等)和类成员(类属性、类函数、构造函数等)的时候作用范围也不同，可见性修饰符不能修饰，Kotlin中增加了一个模块可见性`internal`，修改了`protected`的可见范围，Kotlin共有如下四种可见性：
- `private`: 作为类声明时只在本类中可见，作为顶层声明只在当前文件中可见
- `protected`: 只能用于类成员声明，在当前类或子类中可见
- `internal`: 在当前模块中可见
- `public`: 在任何地方都可见

其中，一个模块指的可以是：
- 一个IntelliJ IDEA模块
- 一个Maven项目
- 一个Gradle源代码集合(除`test`源代码集合可以访问`internal`声明的`main`外)
- 通过一次调用Ant任务编译的Kotlin源代码集合

*注：*
1. 与Java不同，Kotlin中不加修饰符时的默认可见性为`public`
2. Kotlin的外部类不能访问内部类的`private`成员
3. Kotlin没有包可见性修饰符
4. `getter`访问器的可见性与属性相同
5. 如果有可见性修饰符或注解修饰主构造函数，`constructor`关键字不能省略，如：
```
class A private constructor(a: Int) { ... }
```

####数据类

数据类是专门用于保存某种状态的数据的类，我们可以保存诸如用户信息之类的数据。虽然使用普通类也可以对数据进行存储，但使用Kotlin提供的数据类无疑大大减少了代码量，提高了代码的可读性。

#####数据类的声明

Kotlin的数据类使用`data class`进行声明，要求主构造函数的参数必须声明为`var`或`val`的，如：
```
data class User(val name: String, var password: String)
```
上述代码声明了一个`User`数据类，省略了类体，Kotlin允许声明不包含类体的类。

#####数据类的函数

Kotlin数据类底层为我们重写了父类中的`equals()`、`hashCode()`、`toString()`函数，并且增加了一个`copy()`函数。

重写后的`equals()`函数会比较主构造函数中的所有属性，如果全部相等，函数返回`true`；`toString()`函数会将所有属性拼接成一个字符串，其格式为`类名(参数1=参数值, 参数2=参数值, ...)`；`copy()`函数用于复制一个已有的数据类对象，复制的同时允许修改某几个参数(可以是`val`声明的参数)，示例代码如下：
```
fun main(args: Array<String>) {
    val John = User("John", "123456")
    val Mike = John.copy(name = "Mike")
    println(Mike)   //和Java相同，默认调用它的toString()函数
}

data class User(val name: String, var password: String)
```
在使用`copy()`函数的时候，多数情况下需要像上面一样使用命名参数。

#####解构数据类

解构是Kotlin中的一种语法，可以用于数据类或者集合的遍历。
```
    val John = User("John", "123456")
    val Mike = John.copy("Mike")
    var (name, password) = John
    println(name)
    println(password)
    val (_, password2) = Mike
    println(password2)
```
上述代码第3行的含义是对数据类对象`John`进行解构，按顺序得到两个参数的值分别赋值给`var`声明的变量`name`和`password`(这里利用了Kotlin的类型推断省略了变量类型)，当不需要某个参数的值时，可以使用`_`占位，如第6行。

上例中第3行解构声明将被编译成：
```
    val name = John.component1()
    val password = John.component2()
```

####继承与多态

#####继承类

Kotlin中声明的类默认是不可以被继承的，相当于Java中用`final`修饰的类，如果需要声明可以被继承的类，需要使用关键字`open`声明，如声明一个可以被继承的`Person`类：
```
open class Person(val name: String, var age: Int)   //省略了类体
```

Kotlin中继承不使用关键字(Java中使用`extends`关键字)，也是在参数列表后面使用冒号，然后加上`父类名(参数列表)`继承相应的类，最多只能继承一个类。

当子类有主构造函数时，必须在继承父类的时候提供任一构造函数的参数列表，如果只有默认构造函数，也需要一对小括号，如：
```
class Student(val studentName: String, var studentAge: Int, var school: String) : Person(studentName, studentAge)   //省略了类体
```

当子类没有主构造函数(默认构造函数也是主构造函数)时，次构造函数之间进行重载，这个时候继承父类的声明处不需要加上一对小括号，每个次构造函数参数列表的括号后面使用`super(参数列表)`调用父类构造函数，如：
```
open class Person(private val name: String, private var age: Int)

class Student : Person {
    private var school: String
    constructor(name: String, age: Int, school: String) : super(name, age) {
        this.school = school
    }
    constructor(firstName: String, lastName: String, age: Int, school: String) : super("$firstName.$lastName", age) {
        this.school = school
    }
}
```

#####覆盖

在Java中当声明的成员变量名与父类相同，声明的成员方法名称与父类相同且参数列表和父类数量相同且对应的参数类型相同，则会被认为是对父类成员的覆盖，Java中可以使用`@Override`注解来使编译器强制检查成员方法是覆盖父类而非重载。

在Kotlin中当重写父类成员(包括成员变量和成员函数)时，要求必须使用`override`关键字对成员进行修饰，不能省略该关键字。被重写的成员变量类型必须与重写后的类型一致。由于Kotlin中默认的成员都是`final`的，所以允许被覆盖的成员变量和函数一般也需要用`open`关键字修饰，如：
```
fun main(args: Array<String>) {
    println(Student("John.Smith", school = "希望小学"))
}

open class Person(private val name: String,
                  private var age: Int,
                  open val gender: String = "男") {
    constructor(name: String, gender: String = "男") :
            this(name, 18, if(gender == "男") "男" else "女")

    override fun toString(): String {
        return """姓名：$name
            |性别：$gender
            |年龄：$age
        """.trimMargin()
    }
}

class Student(name: String,
              age: Int = 12,
              override val gender: String = "male",
              var school: String) :
        Person(name, age, if (gender == "male") "男" else "女") {

    override fun toString(): String {
        return super.toString() + "\n学校：$school"
    }
}
```
上述代码中父类`Person`重写了`Any`中的`toString()`函数，声明了一个`open`修饰的`gender`属性；其子类`Student`重写了`gender`属性和父类`Person`的`toString()`函数，其中使用`super.toString()`调用了父类`Person`的`toString()`方法，在子类中，可以使用`super.属性名`、`super.函数名(参数列表)`调用父类对象的成员，这与Java基本一致。

*注：*
重写后的成员可以有新的可见性修饰符，但必须保证其可见性范围包含父类对应成员的可见性范围，其中比较特殊是情况是父类成员用`protected`修饰时子类成员不可以用`internal`修饰。

#####多态

Kotlin中的多态与Java基本相同，允许将一个实例赋值给用它的父类声明的变量：
```
fun main(args: Array<String>) {
    val John: Person = Student("John", 10, "希望小学")
}

open class Person(val name: String, var age: Int)

class Student(val studentName: String, var studentAge: Int, var school: String) : Person(studentName, studentAge)
```

Kotlin中使用`is`和`!is`进行类型检查，类似Java中的`instanceof`，如：
```
    val John: Person = Student("John", 10, "希望小学")
    println(John is Student)
    val Mike = Person("Mike", 18)
    println(Mike !is Student)
```

当子类实例被赋值给父类类型的引用变量时，如果调用一个函数父类和子类中均存在，始终是调用子类中的函数。子类中存在而父类中不存在的函数，使用父类的引用可能无法访问这样的函数，此时可以使用`as`和`as?`进行类型转换。
```
    val John: Person = Student("John", 10, "希望小学")
    println(John.school)    //编译错误，无法访问school属性，Person类中不存在该属性
    val John2 = John as Student
    println(John2.school)
```
当使用`as`运算符时，如果类型不兼容会抛出`ClassCastException`异常，为了避免异常，可以使用安全转换运算符`as?`进行类型转换，如果类型不兼容则会返回`null`。

*注：*
在最新版的Kotlin中，类型推断支持的更加完善，当我们对变量的类型判断过后，编译器会自动将变量的类型转换为相应类型，从而免去类型转换的过程，上面的代码可以改为：
```
    val John: Person = Student("John", 10, "希望小学")
    if(John is Student)
        println(John.school)
```

####内部类与嵌套类

嵌套类是指声明在一个类内部的类，这个类被称为外部类。而内部类则是一种特殊的嵌套类，内部类可以访问外部类的引用，而嵌套类不可以。

Java语言中默认声明在一个类内部的类就是内部类，Kotlin中声明内部类需要使用`inner`关键字，在实例化内部类之前，需要先实例化外部类，如：
```
class Outer {
    private val bar: Int = 1
    inner class Inner {
        fun foo() = bar
    }
}

fun main(args: Array<String>) {
    val demo = Outer().Inner().foo()
    println(demo)
}
```
上述代码在外部类`Outer`内部定义了一个内部类`Inner`，调用`foo()`函数时先创建了`Outer()`实例，又创建了`Inner()`实例，然后再调用函数。从代码中可以看出，内部类能够访问外部类的成员属性。

Kotlin中默认的嵌套类相当于Java中用`static`修饰的嵌套类，它不必实例化外部类就可以创建嵌套类对象，但不能访问外部类的成员，如：
```
class Outer {
    private val bar: Int = 1
    class Nested {
        fun foo() = 2
    }
}

fun main(args: Array<String>) {
    val demo = Outer.Nested().foo()
    println(demo)
}
```

局部类是指在函数(方法)中声明的类，与Java基本一致。

####抽象类与接口

#####抽象类

Kotlin语言的抽象类与Java基本一致，使用`abstract`关键字进行声明类及其抽象成员(包括抽象属性和抽象函数)。抽象类及其抽象成员默认都是可以被继承或覆盖的，不需要再使用`open`关键字。抽象类有构造函数，也可以继承父类或实现接口。抽象类中可以没有抽象成员，但有抽象成员的类必须声明为抽象类。

```
abstract class Employee {
    val base = 2000
    abstract val name: String
    abstract fun salary()
}

class Manager(override val name: String) : Employee() {
    override fun salary() {
        println("经理的工资是${base * 5}")
    }
}

class Worker(override val name: String) : Employee() {
    override fun salary() {
        println("工人的工资是${base * 3}")
    }
}
```
上述代码中抽象类`Employee`中声明了一个抽象属性`name`和抽象函数`salary()`，抽象属性没有初始值，抽象函数没有函数体。子类中使用`override`关键字进行重写，抽象类也有默认构造方法，子类进行继承时需要调用其中一个构造方法。

#####接口

Kotlin的接口与Java8以后的接口类似，使用`interface`关键字声明，可以在接口内使用具体属性和带有函数体的函数。但接口不保存状态，即接口中的具体属性没有支持字段，只能有`getter`访问器。Kotlin语言中的类只能继承一个类(单继承)，但可以实现多个接口，父类和实现的接口都要放在冒号后面，如果有多个，可以用逗号`,`分开，接口没有构造函数，不能加小括号。另外，接口也也可以继承接口，接口的示例代码如下：

```
interface Employee {
    val base: Int       //具体属性
        get() = 2000    //具体属性的getter访问器
    val name: String    //抽象属性
    fun salary()        //抽象函数
    fun display() {     //具体函数
        println("""I'm a ${javaClass.name}
            |My name is $name
        """.trimMargin())
    }
}

class Worker(name: String) : Employee {
    override val name = name
    override fun salary() {
        println("工人的工资是${base * 3}")
    }
}

class Manager(override val name: String) : Employee {
    //简写在主构造函数参数列表中的属性也可以用override、private等关键字修饰
    override fun salary() {
        println("经理的工资是${base * 5}")
    }
}
```

####`object`关键字

#####对象声明

Java中实现一个简单(非线程安全)的单例模式可以使用下面的形式(饿汉式)：
```
//Java代码
class Singleton {
    private static Singleton instance = new Singleton();
    //私有化构造方法
    private Singleton() {}
    //声明类方法getInstance()
    public static Singleton getInstance() {
        return instance;
    }
}
```

Kotlin中没有静态属性、静态方法以及静态块(Java中用`static`关键字声明)，而是引入了对象声明。对象声明将单例设计模式语法化，使用`object`关键字可以声明一个非线程安全的单例对象，如：`object Singleton   //省略了类体`(饿汉式)，其用法与`class`类似，可以继承父类或实现接口，但没有构造函数，当父类存在构造函数时，继承时必须调用其中一个构造函数。

对象声明可以声明为顶层对象，或者声明在其他的类或对象中，但不能声明在函数中，也不能作为内部类。对象声明可以包含`init`代码块、成员属性、成员函数以及嵌套类等，访问一个对象时只能通过`object`的名称，而不能创建实例。

#####对象表达式

在Java中为了使用抽象类或实现接口，通常会使用匿名内部类，如处理按钮的单击事件：
```
//Java代码
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ButtonClick {
    public static void main(String[] args) {
        Frame frame = new Frame("按钮单击事件");
        Button btn = new Button("按钮");
        frame.add(btn);
        frame.pack();
        frame.setVisible(true);
        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("按钮被单击");
            }
        });
    }
}
```

`object`关键字可以声明对象表达式，可以不提供`object`的名称，通过冒号后面加上父类构造函数或接口名来继承抽象类、具体类或实现接口，也可以省略默认继承`Any`类，该表达式将返回该对象的唯一实例。使用对象表达式实现上面的代码如下：
```
//Kotlin代码
import java.awt.*
import java.awt.event.ActionEvent
import java.awt.event.ActionListener

fun main(args: Array<String>) {
    val frame = Frame("按钮单击事件")
    val btn = Button("按钮")
    frame.add(btn)
    frame.pack()
    frame.isVisible = true
    btn.addActionListener(object : ActionListener {
        override fun actionPerformed(e: ActionEvent?) {
            println("按钮被单击")
        }
    })
}
```

#####伴生对象

Java中有类层次的成员属性和成员方法，它们使用`static`关键字修饰。由于这不符合纯面向对象的设计目标，并且在代码中使用`static`修饰符可能会有副作用，因此Kotlin中抛弃了静态方法和静态成员。Kotlin可以通过伴生对象的方式实现类似`static`关键字的功能，并且其功能要更加强大、灵活。

伴生对象在类中使用`companion`关键字修饰一个对象声明(`object`)，通常情况下伴生对象省略对象名(此时默认的对象名是`Companion`)，伴生对象将在类加载时被创建，使用Kotlin对伴生对象内的成员进行访问时，可以像静态成员一样不使用伴生对象名直接访问，如：
```
class Test {
    companion object {
        var a = 1
        val b = "abc"
        fun c() = b + a
    }
}

fun main(args: Array<String>) {
    //通过伴生对象名类访问，这种情况和普通的类内部的object对象相同
    println(Test.Companion.a)
    //访问伴生对象的成员可以省略伴生对象名
    println(Test.b)
    println(Test.c())
}
```

*注：*
- Kotlin最多允许存在一个伴生对象。
- 伴生对象可以继承类或实现接口。
- Kotlin默认声明的嵌套类不是内部类，不能访问其外部类的成员，但可以访问其外部类伴生对象(`companion object`)中的成员。
- 使用Java调用Kotlin的伴生对象时，需要使用类似`类名.伴生对象名.函数/属性名`来进行访问。如果想要生成相应的静态成员，可以在Kotlin中使用`@JvmField`注解修饰成员，如果需要生成静态的`getter`、`setter`访问器，可以使用`@JvmStatic`注解。

#####单例模式

- 懒汉式：前面对象声明部分提到了Kotlin中饿汉式单例的声明方法，即`object Singleton`，与Java相比其形式十分简洁，


####枚举类与密封类
<!-- 下一节 -->
###异常处理
###泛型

###函数式编程
####内联函数
###尾递归
需要本教程MarkDown版本的请联系QQ：2336233438