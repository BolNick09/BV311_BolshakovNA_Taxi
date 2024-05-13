// BV311_BolshakovNA_Taxi.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

const int busCap = 16;
int passDay(int basePassInterv, int baseBusInterv, bool isEnd);//функция, которая симулирует 1 день остановки. На выходе выдает среднее время ожидания за день

int main()
{
    srand(time(nullptr));
    

    //замена BusInterv на baseBusInterv. Нужна для вычисления фактического интервала
    std::cout << "Enter bus interval\n";
    int baseBusInterv;
    std::cin >> baseBusInterv;


    std::cout << "Enter passanger interval\n";
    int basePassInterv;
    std::cin >> basePassInterv;

    std::cout << "Is end station? (0/1)\n";
    bool isEnd;
    std::cin >> isEnd;

    std::cout << "Enter target average time of waiting\n";
    int targetTime;
    std::cin >> targetTime;

    while (passDay(basePassInterv, baseBusInterv, isEnd) > targetTime)
    {
        baseBusInterv *= 0.95;//уменьшение на 5% интервала движения автобусов до достижения требуемого времени ожидания пассажиров
    }

    std::cout << "required bus interval:" << baseBusInterv;



    
}


int passDay(int basePassInterv,int baseBusInterv, bool isEnd)
{
    //вектор ожидания пассажиров. Каждый элемент - пассажир, значение элемента - время ожидания
    std::vector <int> waitTimes;
    
    int passangers = 0;
    int minute = 0;

    int passInterv;
    int busInterv;
    std::string timeOfDay;

    int averageOfDay = 0;//для подсчета среднего за день
    int takeCount = 0;

    system("cls");
    while (minute < 1440)
    {
        minute++;

        //изменение интервала в зависимости от времени суток
        int hours = (minute % 1440) / 60;
        if (hours < 10)//утро 
        {
            passInterv = basePassInterv * 0.7;
            busInterv = baseBusInterv * 0.7;
            timeOfDay = "Morning";

        }
        else if (hours < 16)//день 
        {
            passInterv = basePassInterv;
            busInterv = baseBusInterv;
            timeOfDay = "Day";
        }
        else if (hours < 20)//вечер 
        {
            passInterv = basePassInterv * 0.8;
            busInterv = baseBusInterv * 0.8;
            timeOfDay = "Evening";
        }
        else//ночь 
        {
            passInterv = basePassInterv * 2;
            busInterv = baseBusInterv * 2;
            timeOfDay = "Night";
        }

        if (isEnd)//если конечная, частота пассажиров и автобусов удваивается
        {
            passInterv *= 0.5;
            busInterv *= 0.5;
        }

        //увеличение времени ожидания каждого пассажира
        if (waitTimes.size())
        {
            for (size_t i = 0; i < waitTimes.size(); i++)
                waitTimes[i]++;
        }
        //Прибытие нового пассажира, вероятность определяется passInterv
        if (!(rand() % passInterv))
        {
            passangers++;
            waitTimes.push_back(0);
            std::cout << "Passangers on stop: " << passangers << std::endl;
        }
        //Прибытие нового автобуса, вероятность определяется busInterv
        if (!(rand() % busInterv))
        {
            int filled = rand() % (busCap + 1);//случайное количество пассажиров в прибывшем автобусе
            std::cout << "Filled in arrived bus: " << filled << std::endl;

            int canTake = busCap - filled;//сколько может взять
            int take = std::min(canTake, passangers);//автобус взял либо сколько мог, либо всех
            std::cout << "Bus took : " << take << " passangers" << std::endl;

            if (take)
            {
                passangers -= take;
                int sum = 0;
                for (size_t i = 0; i < take; i++)//цикл по тем, кого взяли
                {
                    int wait = waitTimes[0];
                    waitTimes.erase(waitTimes.begin());
                    sum += wait;                    
                }
                sum /= take;
                std::cout << timeOfDay << ": Average wait time: " << sum << std::endl ;
                takeCount++;
                averageOfDay += sum;
            }
        }
    }
    averageOfDay /= takeCount;
    std::cout << ": Average wait time of all day: " << averageOfDay << std::endl << std::endl;
    return averageOfDay;
}
