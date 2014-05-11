#include "vlpr.h"
#include <QtGui/QWidget>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QGroupBox>
#include <QtGUI/QLabel>
#include <QtGUI/QAction>
#include <QtGUI/QToolBar>
#include <QtGUI/QFileDialog>
#include <QtGUI/QTextEdit>
#include <QtGUI/QSizePolicy>
#include <QtGUI/QScrollArea>
#include <QtCore/QDateTime>

VLPR::VLPR(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	//设置窗口全屏
	ui.setupUi(this);
	this->showMaximized();

	//获取屏幕大小
	int x = this->width();
	int y = this->height();


	//初始化菜单栏
	createActions();
    createMenus();

	//初始化窗口控件
	cenWidget = new QWidget(this);
	setCentralWidget(cenWidget);

	groupBox1 = new QGroupBox("原始图片",cenWidget);
	groupBox1->setGeometry(x*0.01,y*0.01,x*0.5,y*0.6);
	scrollArea1 = new QScrollArea(groupBox1);
	scrollArea1->resize( groupBox1->width()*0.93 , groupBox1->height()*0.93 );
	scrollArea1->move(  (groupBox1->width()-scrollArea1->width() )/2,
		(groupBox1->height()-scrollArea1->height() )/2);
	scrollArea1->setBackgroundRole(QPalette::Dark);
	label1 = new QLabel(scrollArea1);
	scrollArea1->setWidget(label1);

	groupBox2 = new QGroupBox("目标车牌",cenWidget);
	groupBox2->setGeometry(x*0.57,y*0.05,x*0.35,y*0.3);
	scrollArea2 = new QScrollArea(groupBox2);
	scrollArea2->resize(groupBox2->width()*0.93, groupBox2->height()*0.85);
	scrollArea2->move((groupBox2->width()-scrollArea2->width() )/2,
		(groupBox2->height()-scrollArea2->height() )/2);
	label2 = new QLabel(scrollArea2);
	scrollArea2->setBackgroundRole(QPalette::Dark);
	scrollArea2->setWidget(label2);

	scrollArea3 = new QScrollArea(cenWidget);
	scrollArea3->resize(x*0.5,y*0.3);
	scrollArea3->move(x*0.01,y*0.65);
	logEdit = new QTextEdit(scrollArea3);
	scrollArea3->setWidget(logEdit);
	logEdit->resize(scrollArea3->size());
	logEdit->setReadOnly(true);
	updateLog("欢迎进入三峡大学车牌号识别系统");
}

VLPR::~VLPR()
{

}

//更新日志窗口
void VLPR::updateLog(QString text)
{
	QDateTime time = QDateTime::currentDateTime();//获取系统时间
	QString t = ">"+time.toString("hh:mm:ss");
	t.append(" "+text+"\n");
	logEdit->setPlainText(logEdit->toPlainText()+t);
}

//显示图片
void VLPR::showImg(QLabel *label,QImage img)
{
	if(label != NULL)
	{
		label->setPixmap(QPixmap::fromImage(img));
		label->resize(label->pixmap()->size());
	}
}

//打开图像
void VLPR::on_OpenImage_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "./Car", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
	image = cv::imread(fileName.toLocal8Bit().data(),-1);

	if(fileName != "")
	{
		QImage img=MatToQImage(image);
		showImg(label1,img);
		updateLog("成功打开图片 "+fileName);
	}
	else
		updateLog("未能成功打开图片");
}

//显示原始图片
void VLPR::on_Show_Image_clicked()
{
	showImg(label1,MatToQImage(image));
}

//图片灰度化
void VLPR::on_Gray_clicked()
{
	gray = cvtImg(image);
	showImg(label1,MatToQImage(gray));
}

//高斯平滑滤波
void VLPR::on_blur_clicked()
{
	gray = gaussian(gray);
	showImg(label1,MatToQImage(gray));
}

//利用sobel算子进行边缘检测
void VLPR::on_edgeDetect_clicked()
{
	gray = Sobel(gray);
	showImg(label1,MatToQImage(gray));
}

//图片二值化
void VLPR::on_thres_clicked()
{
	thres(gray);
	showImg(label1,MatToQImage(gray));
}

//形态学处理
void VLPR::dilateErode()
{
	morphology(gray);
	showImg(label1,MatToQImage(gray));
}

//定位车牌
void VLPR::on_locate_clicked()
{
	car = getLocation(gray,image);
	showImg(label2,MatToQImage(car));
}

void VLPR::createActions() {
    // QAction: 一建立, 二设置属性, 如图标, 快捷键, 事件处理.
    openAction = new QAction("打开", this);
	QObject::connect(openAction, SIGNAL(triggered()), this, SLOT(on_OpenImage_clicked()));
	quitAction = new QAction("关闭", this);
	QObject::connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
	grayAction = new QAction("灰度化",this);
	QObject::connect(grayAction, SIGNAL(triggered()), this, SLOT(on_Gray_clicked()));
	imgAction = new QAction("查看原图",this);
	QObject::connect(imgAction,  SIGNAL(triggered()), this, SLOT(on_Show_Image_clicked()));
	edgeDetectAction = new QAction("边缘检测",this);
	QObject::connect(edgeDetectAction, SIGNAL(triggered()), this, SLOT(on_edgeDetect_clicked()));
	thresAction = new QAction("二值化",this);
	QObject::connect(thresAction,SIGNAL(triggered()), this, SLOT(on_thres_clicked()));
	morphologyAction = new QAction("膨胀腐蚀",this);
	QObject::connect(morphologyAction,SIGNAL(triggered()),this,SLOT(dilateErode()));
	blurAction = new QAction("高斯平滑滤波",this);
	QObject::connect(blurAction,SIGNAL(triggered()), this, SLOT(on_blur_clicked()));
	locateAction = new QAction("定位车牌",this);
	QObject::connect(locateAction,SIGNAL(triggered()),this,SLOT(on_locate_clicked()));
}

void VLPR::createMenus() {

	//文件菜单
    fileMenu = menuBar()->addMenu("文件");
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
	fileMenu->addAction(quitAction);
    fileMenu->addSeparator();

	//预处理菜单
	preDeal = menuBar()->addMenu("预处理");
	preDeal->addAction(imgAction);
	preDeal->addAction(grayAction);
	preDeal->addAction(blurAction);
    preDeal->addSeparator();

	//车牌定位菜单
	locateMenu = menuBar()->addMenu("车牌定位");
	locateMenu->addAction(thresAction);
	locateMenu->addAction(edgeDetectAction);
	locateMenu->addAction(morphologyAction);
	locateMenu->addAction(locateAction);

	//字符分割菜单
	divMenu = menuBar()->addMenu("字符分割");

	//字符识别菜单
	charRecoMenu = menuBar()->addMenu("字符识别");
}
