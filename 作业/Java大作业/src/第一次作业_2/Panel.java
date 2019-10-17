package 第一次作业_2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class DriverPanel extends JPanel {
    private JLabel photoLabel;
    private JTextField name, sex, nationality, driverAddress, birthDate, driverIssueDate, validFrom,
            classPermitted, validFor;

    public DriverPanel(Driver driver) {
        Box BoxV1, BoxV2;

        JLabel fileNoLabel = new JLabel("档案编号：" + driver.getFileNo());

        photoLabel = new JLabel();
        Image photo = driver.getPhoto();
        if (photo != null) {
            ImageIcon imgIcon= new ImageIcon(photo);
            photoLabel.setSize(imgIcon.getIconWidth(), imgIcon.getIconHeight());
            photoLabel.setIcon(imgIcon);
        }
        JButton changeDriverImgButton = new JButton("更改图片");
        JPanel photoPanel = new JPanel(new FlowLayout());
        photoPanel.add(photoLabel);
        photoPanel.add(changeDriverImgButton);

        BoxV1 = Box.createVerticalBox();
        BoxV1.add(new Label("姓名："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("性别："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("国籍："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("住址："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("出生日期："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("发证日期："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("准驾车型："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("有效起始日期："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("有效期限："));

        BoxV2 = Box.createVerticalBox();
        name = new JTextField(driver.getName());
        sex = new JTextField(driver.getSex());
        nationality = new JTextField(driver.getNationality());
        driverAddress = new JTextField(driver.getAddress());
        birthDate = new JTextField(driver.getBrithDate());
        driverIssueDate = new JTextField(driver.getIssueDate());
        validFrom = new JTextField(driver.getValidFrom());
        classPermitted = new JTextField(driver.getClassPermitted().toString());
        validFor = new JTextField(driver.getValidFor());
        BoxV2.add(name);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(sex);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(nationality);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(driverAddress);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(birthDate);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(driverIssueDate);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(classPermitted);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(validFrom);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(validFor);

        Box baseBox = Box.createHorizontalBox();
        baseBox.add(BoxV1);
        baseBox.add(Box.createHorizontalStrut(10));
        baseBox.add(BoxV2);
        baseBox.setSize(10, 10);

        JButton saveButton = new JButton("保存司机信息");

        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        add(fileNoLabel);
        add(photoPanel);
        add(baseBox);
        add(saveButton);

        /* 事件 */
        changeDriverImgButton.addMouseListener(new onClickChangeDriverImgButton());
        /* 匿名函数实现单击事件 */
        saveButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                String nameText = name.getText(),
                        sexText = sex.getText(),
                        nationalityText = nationality.getText(),
                        addressText = driverAddress.getText(),
                        birthDateText = birthDate.getText(),
                        issueDateText = driverIssueDate.getText(),
                        classPermittedText = classPermitted.getText(),
                        validFromText = validFrom.getText(),
                        validForText = validFor.getText();
                if (!sexText.equals("男") && !sexText.equals("女")) {
                    JOptionPane.showMessageDialog(null, "性别只能为男或女！", "错误：", JOptionPane.ERROR_MESSAGE);
                    return;
                } else if (General.checkDate(birthDateText) == null) {
                    JOptionPane.showMessageDialog(null, "输入的出生日期有误！格式为：yyyy-MM-dd", "错误：", JOptionPane.ERROR_MESSAGE);
                    return;
                } else if (General.checkDate(issueDateText) == null) {
                    JOptionPane.showMessageDialog(null, "输入的初次领证日期有误！格式为：yyyy-MM-dd", "错误：", JOptionPane.ERROR_MESSAGE);
                    return;
                } else if (General.checkDate(validFromText) == null) {
                    JOptionPane.showMessageDialog(null, "输入的有效起始日期有误！格式为：yyyy-MM-dd", "错误：", JOptionPane.ERROR_MESSAGE);
                    return;
                } else if (nameText.equals("") || nationalityText.equals("") || addressText.equals("") || validForText.equals("")) {
                    JOptionPane.showMessageDialog(null, "任一项不能为空！", "错误：", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                driver.setPhoto(((ImageIcon) photoLabel.getIcon()).getImage());
                try {
                    driver.setClassPermitted(Driver.ClassPermitted.valueOf(classPermittedText));
                } catch (IllegalArgumentException exception) {
                    JOptionPane.showMessageDialog(null, "输入的准驾车型有误！必须为A1、A2、A3、B1、B2、C1、C2、C3、C4、C5、D、E、F、M、N、P之一", "错误", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                driver.setName(nameText);
                driver.setSex(sexText);
                driver.setNationality(nationalityText);
                driver.setAddress(addressText);
                driver.setBirthDate(birthDateText);
                driver.setIssueDate(issueDateText);
                driver.setValidFrom(validFromText);
                driver.setValidFor(validForText);
                JOptionPane.showMessageDialog(null, "保存成功！", "信息：", JOptionPane.INFORMATION_MESSAGE);
            }
        });
    }

    /* 司机选择夹更改图片按钮 */
    private class onClickChangeDriverImgButton extends MouseAdapter {
        @Override
        public void mouseClicked(MouseEvent e) {
            JFileChooser fileChooser = new JFileChooser();
            if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
                if (photoLabel != null) {
                    String path = fileChooser.getSelectedFile().getAbsolutePath();
                    photoLabel.setIcon(new ImageIcon(path));
                }
            }
        }
    }
}

class CarPanel extends JPanel {
    private JTextField plateNo, vehicleType, owner, address, identificationNo, registerDate,
            issueDate, fuelTankCapacity, currentFuelQuantity, weight, loadCapacity, totalMileage;
    public CarPanel(Car car) {
        Box BoxV1, BoxV2;

        JLabel engineNoLabel = new JLabel("发动机号码：" + car.getEngineNo());
        JLabel appearanceLabel = new JLabel("外观图片：");
        JLabel appearanceImgLabel = new JLabel();
        Image appearanceImage = car.getAppearanceImage();
        if (appearanceImage != null) {
            ImageIcon imgIcon = new ImageIcon(appearanceImage);
            appearanceImgLabel.setSize(imgIcon.getIconWidth(), imgIcon.getIconHeight());
            appearanceImgLabel.setIcon(imgIcon);
        }
        JButton changeAppearanceImgButton = new JButton("更改图片");
        JPanel appearancePanel = new JPanel(new FlowLayout());
        appearancePanel.add(appearanceImgLabel);
        appearancePanel.add(changeAppearanceImgButton);

        JLabel licenseLabel = new JLabel("行驶证照片：");
        JLabel licenseImgLabel = new JLabel();
        Image lisenceImage = car.getLicenseImage();
        if(lisenceImage!=null) {
            ImageIcon imgIcon = new ImageIcon(lisenceImage);
            licenseImgLabel.setSize(imgIcon.getIconWidth(), imgIcon.getIconHeight());
            licenseImgLabel.setIcon(imgIcon);
        }
        JButton changeLicenseImgButton = new JButton("更改图片");
        JPanel licensePanel = new JPanel(new FlowLayout());
        licensePanel.add(licenseImgLabel);
        licensePanel.add(changeLicenseImgButton);

        BoxV1 = Box.createVerticalBox();
        BoxV1.add(new Label("汽车号牌："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("车辆类型："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("所有人："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("住址："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("车辆识别号VIN："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("注册日期："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("发证日期："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("油箱容量："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("当前容量："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("重量："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("载重量："));
        BoxV1.add(Box.createVerticalStrut(8));
        BoxV1.add(new Label("总行驶公里数："));

        BoxV2 = Box.createVerticalBox();
        plateNo = new JTextField(car.getPlateNo());
        vehicleType = new JTextField(car.getVehicleType());
        owner = new JTextField(car.getOwner());
        address = new JTextField(car.getAddress());
        identificationNo = new JTextField(car.getIdentificationNo());
        registerDate = new JTextField(car.getRegisterDate());
        issueDate = new JTextField(car.getIssueDate());
        fuelTankCapacity = new JTextField(String.valueOf(car.getFuelTankCapacity()));
        currentFuelQuantity = new JTextField(String.valueOf(car.getCurrentFuelQuantity()));
        weight = new JTextField(String.valueOf(car.getWeight()));
        loadCapacity = new JTextField(String.valueOf(car.getLoadCapacity()));
        totalMileage = new JTextField(String.valueOf(car.getTotalMileage()));

        BoxV2.add(plateNo);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(vehicleType);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(owner);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(address);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(identificationNo);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(registerDate);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(issueDate);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(fuelTankCapacity);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(currentFuelQuantity);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(weight);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(loadCapacity);
        BoxV2.add(Box.createVerticalStrut(8));
        BoxV2.add(totalMileage);

        Box baseBox = Box.createHorizontalBox();
        baseBox.add(BoxV1);
        baseBox.add(Box.createHorizontalStrut(10));
        baseBox.add(BoxV2);
        baseBox.setSize(10, 10);

        JButton saveButton = new JButton("保存汽车信息");

        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        add(engineNoLabel);
        add(appearanceLabel);
        add(appearancePanel);
        add(licenseLabel);
        add(licensePanel);
        add(baseBox);
        add(saveButton);

        /* 事件 */
        /* 汽车选择夹外观更换照片 */
        changeAppearanceImgButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
                    String path = fileChooser.getSelectedFile().getAbsolutePath();
                    appearanceImgLabel.setIcon(new ImageIcon(path));
                }
            }
        });
        /* 汽车选择夹行驶证更换照片 */
        changeLicenseImgButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
                    String path = fileChooser.getSelectedFile().getAbsolutePath();
                    licenseImgLabel.setIcon(new ImageIcon(path));
                }
            }
        });
        /* 保存汽车信息 */
        saveButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                String plateNoText = plateNo.getText(),
                       vehicleTypeText = vehicleType.getText(),
                       ownerText = owner.getText(),
                       addressText = address.getText(),
                       identificationNoText = identificationNo.getText(),
                       registerDateText = registerDate.getText(),
                       issueDateText = issueDate.getText(),
                       fuelTankCapacityText = fuelTankCapacity.getText(),
                       currentFuelQuantityText = currentFuelQuantity.getText(),
                       weightText = weight.getText(),
                       loadCapacityText = loadCapacity.getText(),
                       totalMileageText = totalMileage.getText();

                if (General.checkDate(registerDateText) == null) {
                    JOptionPane.showMessageDialog(null, "输入的注册日期有误！格式为：yyyy-MM-dd", "错误：", JOptionPane.ERROR_MESSAGE);
                    return;
                } else if (General.checkDate(issueDateText) == null) {
                    JOptionPane.showMessageDialog(null, "输入的发证日期有误！格式为：yyyy-MM-dd", "错误：", JOptionPane.ERROR_MESSAGE);
                    return;
                } else if (plateNoText.equals("") || vehicleTypeText.equals("") || ownerText.equals("") ||
                        addressText.equals("") || identificationNoText.equals("") ||
                        fuelTankCapacityText.equals("") || currentFuelQuantityText.equals("") ||
                        weightText.equals("") || loadCapacityText.equals("") || totalMileageText.equals("")) {
                    JOptionPane.showMessageDialog(null, "任一项不能为空！", "错误：", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                try {
                    car.setAppearanceImage(((ImageIcon) appearanceImgLabel.getIcon()).getImage());
                    car.setLicenseImage(((ImageIcon) licenseImgLabel.getIcon()).getImage());
                } catch (NullPointerException exception) {
                    //图片保存失败
                }
                car.setPlateNo(plateNoText);
                car.setVehicleType(vehicleTypeText);
                car.setOwner(ownerText);
                car.setAddress(addressText);
                car.setIdentificationNo(identificationNoText);
                car.setRegisterDate(registerDateText);
                car.setIssueDate(issueDateText);
                try {
                    car.setFuelTankCapacity(Double.parseDouble(fuelTankCapacityText));
                    car.setCurrentFuelQuantity(Double.parseDouble(currentFuelQuantityText));
                    car.setWeight(Double.parseDouble(weightText));
                    car.setLoadCapacity(Double.parseDouble(loadCapacityText));
                    car.setTotalMileage(Double.parseDouble(totalMileageText));
                } catch (NumberFormatException exception)
                {
                    JOptionPane.showMessageDialog(null, "后五项必须为数字！", "错误：", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                JOptionPane.showMessageDialog(null, "保存成功！", "信息：", JOptionPane.INFORMATION_MESSAGE);
            }
        });
    }
}