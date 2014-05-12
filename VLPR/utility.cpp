#include"utility.h"

//convert Mat to QImage
QImage MatToQImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
	QImage img;
	return img;
}

void showImg(cv::Mat image)
{
	//Opencv显示
	cvNamedWindow("Test Image");
	cv::imshow("Test Image", image);
}

//图片灰度化
cv::Mat cvtImg(cv::Mat image)
{
	cv::Mat gray = cv::Mat(image.cols,image.rows,image.type());
	if (image.type() == CV_8UC3)
	{
		cv::cvtColor(image,gray,CV_BGR2GRAY);
	}
	else
		gray = image;
	return gray;
}

//高斯平滑滤波
cv::Mat gaussian(cv::Mat image)
{
	cv::Mat image2 = cv::Mat(image.rows,image.cols,image.type());
	GaussianBlur(image,image2,cv::Size(3,3),0);
	return image2;
}

//获取灰度图像像素点
int getElement(cv::Mat image,int i,int j)
{
	if (i < image.rows && i >= 0 && j >= 0 && j < image.cols && image.channels() == 1)
	{
		return (int)(*(image.data+image.step[0]*i + image.step[1]*j));
	}
	else
		return -1;
}

//设置图片像素点
bool setElement(cv::Mat image,int i,int j,int val)
{
	if (i < image.rows && i >= 0 && j >= 0 && j < image.cols && image.channels() == 1)
	{
		*(image.data+image.step[0]*i + image.step[1]*j)=val;
		return true;
	}
	else
		return false;
}

//迭代阈值法获取阈值
void getThres(cv::Mat image,int t,int& res)
{
	int t1=0,t2=0,tnew=0,i=0,j=0;
	int Allt1=0,Allt2=0,accountt1=0,accountt2=0;
	for(i=0;i<image.rows;++i)
	{
		for(j=0;j<image.cols;++j)
		{
			int temp=getElement(image,i,j);
			if(temp < t)
			{
				Allt1+=temp;
				accountt1++;
			}
			else
			{
				Allt2+=temp;
				accountt2++;
			}
		}
	}
	t1=Allt1/accountt1;
	t2=Allt2/accountt2;
	tnew=(t1+t2)*0.5;
	printf("tnew=%d t=%d\n",tnew,t);
	if (tnew==t)
		res=tnew;
	else
		getThres(image,tnew,res);
}

//迭代阈值法二值化
void thres(cv::Mat& image)
{
	int thresMax=0,thresMin=255;
	for(int i=0;i<image.rows;++i)
	{
		for (int j=0;j<image.cols;++j)
		{
			int temp = getElement(image,i,j);
			if(temp > thresMax)
				thresMax=temp;
			else if(temp < thresMin)
				thresMin=temp;
		}
	}
	int thres ;
	getThres(image,(thresMax+thresMin)*0.5,thres);
	cv::Canny(image,image,thres,thresMax*0.7);
}

int max(int a, int b)
{
	return a>b?a:b;
}

//投影法车牌定位
cv::Mat getLocation(cv::Mat image,cv::Mat original)
{
	cv::Mat car = cv::Mat(image.rows,image.cols,image.type());
	int plate_s=-1, plate_n=-1, plate_e=-1, plate_w=-1; //车牌上下左右边界
	int length=0, wide=0; //车牌长度，高度
	int *num = new int[max(image.cols, image.rows)]; //定位数组
	QFile file("../log/log.txt");
	QTextStream stream(&file);

	file.open(QIODevice::WriteOnly); //open log file

	for(int i=0;i<image.rows;++i)
		num[i]=0;
	//统计水平跳变次数
	for(int i=image.rows-1; i >= 0; --i)
	{
		for(int j=0; j < image.cols-1; ++j)
		{
			num[i]+=qAbs( getElement(image,i,j+1)-getElement(image,i,j) )/255;
		}
	}
	//均值平滑处理
	for(int i=1; i < image.rows-1 ; ++i)
		num[i] = (num[i-1]+num[i+1])/2;

	for(int i=image.rows-2; i >= 0; --i)
	{
		if(num[i]>= 14)
		{
			plate_s = i;
			--i;
			while( i >= 0 && num[i] >= num[i+1] )
				i--;
			++i;
			while( i >= 0 && num[i] >= 14 )
				i--;
			++i;
			plate_n = i;
			wide = plate_s - plate_n +1;
			length = wide * 440 / 140;
			if(! (wide>= image.rows*0.05 && wide <= image.rows*0.5
				&& length < image.cols && length >= 0) )
			{
				i = plate_n-1;
				plate_n = plate_s = -1;
				wide = 0;
				length = 0;
				continue;
			}
			else
				break;
		}
	}
	stream<<"plate_n="<<plate_n<<" plate_s="<<plate_s<<" wide="<<wide<<"\n";
	if (plate_n >= 0 && plate_s < image.rows)
	{
		car = image.rowRange(plate_n,plate_s);
	}
	else
	{
		stream<<"水平分割失败，无法获取上下边界\n";
		return original;
	}
	
	for(int i=0; i < car.cols; ++i)
		num[i]=0;
	for(int i=0; i < car.cols; ++i )
	{
		for(int j=0; j<car.rows; ++j)
			num[i]+=getElement(car,j,i);
	}
	int sum=0, max_wide=0;
	for(int i=0; i < length; ++i)
		sum+=num[i];
	max_wide = sum;
	for(int i=1; i <= car.cols - length; ++i)
	{
		sum = sum - num[i-1] + num[i+length-1];
		if(sum > max_wide)
		{
			max_wide = sum;
			plate_w = i;
		}
	}
	plate_e = plate_w + length - 1;
	stream<<"plate_w="<<plate_w<<" plate_e="<<plate_e<<" length="<<length<<"\n";
	if(plate_w >= 0 && plate_e < car.cols)
	{
		car = original.rowRange(plate_n,plate_s);
		car = car.colRange(plate_w,plate_e);
		//cvNamedWindow("车牌",-1);
		//imshow("车牌",car);
	}
	else
	{
		stream<<"垂直分割失败，无法获取左右边界\n";
		return original;
	}
	
	file.close();
	return car;
}

void charDiv(cv::Mat image)
{

}

//Sobel函数进行边缘检测
cv::Mat Sobel(const cv::Mat& image)
{
	if (image.channels() != 1)
	{
		return image;
	}
	cv::Mat sobel;
	Sobel(image,sobel, CV_32F,2,0,3);
	double minVal, maxVal;
	minMaxLoc(sobel, &minVal, &maxVal);
	cv::Mat result;
	sobel.convertTo(result,CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
	return result;
}

//形态学处理
bool morphology(cv::Mat& image)
{
	if (image.depth() != CV_8U)
	{
		return false;
	}
	//自定义1*3的核进行X方向的膨胀腐蚀
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,cvSize(3,1));
	cv::dilate(image,image,element,cv::Point(1,0),2);
	cv::erode(image,image,element,cv::Point(1,0),4);
	cv::dilate(image,image,element,cv::Point(1,0),2);

	//自定义3*1的核进行Y方向的膨胀腐蚀
	element = cv::getStructuringElement(cv::MORPH_RECT,cvSize(1,3));
	cv::erode(image,image,element,cv::Point(0,1),1);
	cv::dilate(image,image,element,cv::Point(0,1),2);
	return true;
}