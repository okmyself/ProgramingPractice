//import kotlin.reflect.KClass
//import kotlin.reflect.full.declaredFunctions
//import kotlin.reflect.full.declaredMemberProperties
//import kotlin.reflect.full.findAnnotation
//
//annotation class Marker     //基本注解之标记注解
//annotation class MyAnnotation1(val value: String)
//annotation class MyAnnotation2(val value: String = "注解信息", val count: Int = 20)
//
//@Marker
//class Person {
//    @MyAnnotation1(value = "名字")
//    @JvmField
//    var name = "Tony"
//
//    @MyAnnotation2(value = "年龄")
//    var age = 18
//}
//
////@Marker
////fun main(args: Array<String>) {
////    @Marker
////    @MyAnnotation2(value = "实例化Person", count = 1)
////    var p = Person()
////}
//
//@MustBeDocumented
//@Target(AnnotationTarget.CLASS)
//@Retention(AnnotationRetention.RUNTIME)
//annotation class MyAnnotation(val description: String)
//
//@MustBeDocumented
//@Retention(AnnotationRetention.RUNTIME)
//@Target(AnnotationTarget.FUNCTION,
//        AnnotationTarget.PROPERTY,
//        AnnotationTarget.PROPERTY_GETTER,
//        AnnotationTarget.PROPERTY_SETTER)
//annotation class MemberAnnotation(val type: KClass<*> = Unit::class, val description: String)
//
//@MyAnnotation(description = "这是一个测试类")
//class Student {
//    @MemberAnnotation(type = String::class, description = "名字")
//    @set:MemberAnnotation(type = String::class, description = "获得名字")
//    var name: String? = null
//        private set
//
//    @MemberAnnotation(type = Int::class, description = "年龄")
//    @get:MemberAnnotation(type = Int::class, description = "获得年龄")
//    var age: Int = 0
//        private set
//
//    @MemberAnnotation(description = "设置姓名和年龄")
//    fun setNameAndAge(name: String, age: Int) {
//        this.name = name
//        this.age = age
//    }
//
//    override fun toString(): String {
//        return "Person [name=$name, age=$age]"
//    }
//}
////读取运行时注解信息
//fun main(args: Array<String>) {
//    val clz = Student::class
//
//    val ann = clz.findAnnotation<MyAnnotation>()
//    println("类${clz.simpleName}, 注解描述: ${ann?.description ?: "无"}")
//
//    println("--读取成员函数的注解信息--")
//    clz.declaredFunctions.forEach {
//        val ann = it.findAnnotation<MemberAnnotation>()
//        println("函数${it.name}, 注解描述: ${ann?.description ?: "无"}")
//    }
//
//    println("--读取属性的注解信息--")
//    clz.declaredMemberProperties.forEach {
//        val ann = it.findAnnotation<MemberAnnotation>()
//        println("属性${it.name}, 注解描述: ${ann?.description ?: "无"}")
//    }
//}