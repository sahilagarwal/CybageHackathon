#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include <QtWebKitWidgets/QWebView>
//#include <QUrl>
using namespace cv;
using namespace std;

Mat bgr[3];
   // namedWindow("Control", CV_WINDOW_AUTOSIZE);

int iLowH = 0;
int iHighH = 179;

int iLowS = 0;
int iHighS = 255;

int iLowV = 0;
int iHighV = 255;
int value=0;
float area=0.0;
int op;
int bval,rval,gval,mg,mr,mb;
Mat imgOriginal,so;
string img ;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("//home/sahilnew/satellite images/final.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //ui-;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bval=ui->blue->text().toInt();
    rval=ui->red->text().toInt();
    gval=ui->green->text().toInt();
    mg=ui->mGreen->text().toInt();
    mr=ui->mRed->text().toInt();
    mb=ui->mBlue->text().toInt();
    img=ui->input->text().toStdString();
    area = 0.0;
    value = 0;
    if(ui->GREEN->isChecked())
    {
        op = 1;
    }

    else if(ui->RED->isChecked())
    {
        op = 2;
    }

    else if(ui->BLUE->isChecked())
    {
        op = 0;
    }

    /*else if(ui->BLACK->isChecked())
    {
        ui->Result->setText("green");
    }*/

    else if(ui->WHITE->isChecked())
    {

        ui->Result->setText(QString::number(forw(0)));
    }
    else if(ui->rbother->isChecked())
    {
        ui->Result->setText(QString::number(forw(1)));
    }

    ///////////////////////////////////////////////////////////////


    // while (true)
        {

        imgOriginal=imread(img);
       // GaussianBlur(imgOriginal,imgOriginal,Size(3,3),0,0,BORDER_DEFAULT);
        split(imgOriginal,bgr);
        imshow("green",bgr[op]);
    //Mat imgThresholded;

    imshow("Original", imgOriginal); //show the original image

           // if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
           {
            cout<<imgOriginal.size()<<imgOriginal.size().height<<imgOriginal.size().width;
                cout << "esc key is pressed by user" << endl;

            for(int i=0;i<bgr[0].size().width;i+=1)
        {
            for(int j=0;j<bgr[0].size().height;j+=1)
            {
                Scalar cval=bgr[op].at<uchar>(j,i);

                if(op==0 && cval.val[0]>bval && cval.val[0]<mb)
                {
                //cout<<" "<<j<<" "<<i<<" "<<cval.val[0];

                    value++;}
                else if(op==1 && cval.val[0]>gval && cval.val[0]<mg)
                {
                    value++;
                }
                else if(op==2 && cval.val[0]>rval && cval.val[0]<mr)
                {
                    value++;
                }

            }
        }

               // break;
           }

        }

        area=(float)value/bgr[0].total()*100;
        cout<<area<<"%\n"<<bgr[0].total()<<"\n"<<value<<"\n";

        ui->Result->setText(QString::number(area));

}


float MainWindow::forw(int t)
{
    float area=0.0;
    imgOriginal=imread(img);

    imshow("Original", imgOriginal); //show the original image

       // if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
        cout<<imgOriginal.size()<<imgOriginal.size().height<<imgOriginal.size().width;
            cout << "esc key is pressed by user" << endl;

        for(int i=0;i<imgOriginal.size().width;i+=1)
    {
        for(int j=0;j<imgOriginal.size().height;j+=1)
        {
            Scalar cval=imgOriginal.at<uchar>(j,i);
            if(t == 0 && cval.val[0]>240 && cval.val[1]>240 && cval.val[2] >240)
            {
                value++;
            }
            else if(t ==1 && cval.val[0]>bval && cval.val[1]>gval && cval.val[2] >rval && cval.val[0]<mb && cval.val[1]<mg && cval.val[2]<mr)
            {
                value++;
            }
        }
    }

           // break;
       }

    area=(float)value/imgOriginal.total()*100;
   // ui->Result->setText(QString::number(area));

    return area;
}
