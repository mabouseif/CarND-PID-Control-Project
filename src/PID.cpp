#include "PID.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {
}

PID::~PID() {}

void PID::Init(double Kp_gain, double Ki_gain, double Kd_gain) {
    PID::Kp = Kp_gain;
    PID::Ki = Ki_gain;
    PID::Kd = Kd_gain;

    p_error = 0.0;
    i_error = 0.0;
    d_error = 0.0;
    time_step = 0;
    prev_time_step = 0;
    total_distance = 0.0;
    count = 0;
}

void PID::UpdateError(double cte) {


    static double error_summation = 0;
    static double prev_cte = cte;
    error_summation += cte;

    p_error = Kp * cte;
    i_error = Ki * error_summation;
    d_error = Kd * (cte - prev_cte);

    prev_cte = cte;


}

double PID::TotalError() {

    double steer_new = (-p_error  - i_error - d_error);

    if(steer_new >= 1.0)
    {
        steer_new = 1.0;
    }
    if(steer_new <= -1.0)
    {
        steer_new = -1.0;
    }


    return steer_new;


}


void PID::Twiddle(double cte)
{
    static std::vector<double> gains = {Kp, Kd, Ki};
    static std::vector<double> probes = {0.2, 0.2, 0.2};
    static double best_err = 0;
    double new_err = cte;
    double tolerance = 5.0;
    double sum;
    sum = std::accumulate(gains.begin(), gains.end(), 0.0);
    static int i = 0;

    static int flag = 0;

    static int count = 0;

    while(sum < tolerance)
    {
        i = i % 3;
        /*
        for(int j = 0; j < 100000; ++j)
        {
            std::cout << "New Error = " <<  new_err <<  " Best Error = " <<  best_err << std::endl;

        }
        for(int j = 0; j < 100000; ++j)
        {
            std::cout << "i = " <<  i << std::endl;

        }
        */

        switch(flag)
        {

        case(0):
            {


                gains[i] += probes[i];
                Kp = gains[0];
                Kd = gains[1];
                Ki = gains[2];
                if(count == 0)
                {
                    best_err = new_err;
                    ++count;
                }
                flag = 1;

                return;

            }
            break;

        case(1):
            {
                if(new_err < best_err)
                // if(fabs(new_err) < fabs(best_err)) //I REMOVED ABS ERROR
                {
                    best_err = new_err;
                    probes[i] *= 1.1;
                    ++i;
                    flag = 0;


                }else{
                    gains[i] -= 2 * probes[i];
                    Kp = gains[0];
                    Kd = gains[1];
                    Ki = gains[2];
                    flag = 2;

                    return;

                }


            }//case 1
            break;


        case(2):
            {
                if(new_err < best_err)
                // if(fabs(new_err) < fabs(best_err))
                {
                    best_err = new_err;
                    probes[i] *= 1.1;
                    ++i;
                    flag = 0;

                }else{
                    gains[i] += probes[i];
                    probes[i] *= 0.9;
                    ++i;
                    flag = 0;
                }


            } //case 2
            break;

        } // switch bracket







    } // while loop bracket




}





