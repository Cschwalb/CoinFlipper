#include <iostream>
#include <thread>
#include <ctime>
#include <mutex>

std::mutex mtx;
long long respT = 0, respF = 0;

namespace caleb
{
    class flipCoin{
    public:
        bool flip;
        flipCoin()
        {
            flip = false;
        }

        bool flipTheCoin()
        {
            flip = rand() % 2;
            //std::cout<<"Coin: " << flip << std::endl; // takes too long
            return flip;
        }

    };
}

static const void flipCoinTimes(int timesToFlip)
{
    caleb::flipCoin fp = caleb::flipCoin();

    for(int x = 0; x < timesToFlip; x++)
    {
        bool response = fp.flipTheCoin();
        mtx.lock();
        if(response)
        {
            respT ++;
        }
        else
        {
            respF++;
        }
        mtx.unlock();
    }
}


int main() {

    for(int x = 0; x < 32; x ++)
    {
        std::thread th(flipCoinTimes, 125000);
        th.join();
    }

    std::cout<<"ResponseTrue:  " << respT<<std::endl;
    std::cout<<"ResponseFalse:  " << respF << std::endl;
    return 0;
}
