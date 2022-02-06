#include "Param_F.hpp"
#include "Image_TOF.hpp"
#include "Masque.hpp"
#include "Param_E.hpp"
#include "Sol.hpp"
#include "Trosol.hpp"
#include "Lirecsv.hpp"
#include <vector>
using namespace std;
using namespace cv;


int main()
{
    const string file_name = "../data/Depth_246.csv"; //EA
    int opencv_type =  CV_32FC1; 
    cv::Mat image_Depth1;

    Image_TOF Img;
    //image_Depth1 = Img.loadFromCSV(file_name, opencv_type);
    Lirecsv lirecsv;
    float** Depth1 =lirecsv.loadCSV(file_name);
        
    int qq=240;
    int YY=320;
    int size = 240;
    int size1 = 320;
    float Depth2 [240][320]={0};
    for(int i=0;i<qq;i++){
        for(int j=0;j<YY;j++){
         Depth2 [i][j]=Depth1 [i][j];
        }
    }

    cv::Mat image_Depth(size, size1, opencv_type, Depth2);

    for(int j=0; j<240; j++)
    {
        
        for(int i=0; i<320; i++)        
            std::cout<<","<<image_Depth.at<float>(j,i)<<",";
    std::cout<<"###"<<j<<"\n";          
    }

    cv::Mat dep;    
    // ******** Debut ********* //
    Param_F param_f;
    std::vector<double> parametre_deduit = param_f.Param_D(); 
    double min_Val; double max_Val; 
    cv::minMaxIdx(image_Depth,&min_Val, &max_Val);
    Image_TOF Image_tof(image_Depth, parametre_deduit[0], parametre_deduit[1], min_Val, max_Val, 1); 
    // Estimation des sources d'informations : Alpha_estime, Beta_estime, H_estime_Alpha, H_estime_Beta
    cv::Mat Alpha_estime = cv::Mat::zeros(parametre_deduit[0], parametre_deduit[1], opencv_type);
    cv::Mat Beta_estime = cv::Mat::zeros(parametre_deduit[0], parametre_deduit[1], opencv_type);
    cv::Mat H_estime_Alpha = cv::Mat::zeros(parametre_deduit[0], parametre_deduit[1], opencv_type);
    cv::Mat H_estime_Beta = cv::Mat::zeros(parametre_deduit[0], parametre_deduit[1], opencv_type);
    
    Image_tof.Estimer_source_Info(image_Depth, Alpha_estime, Beta_estime, H_estime_Alpha, H_estime_Beta, parametre_deduit, opencv_type); // max_val Okkk, min_val Non

}