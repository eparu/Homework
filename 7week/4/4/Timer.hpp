#ifndef Timer_h
#define Timer_h

class Timer
{
public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;
    using duration_t = clock_t::duration;
    Timer(const std::string& timer_name = "Untitled") : m_timer_name(timer_name), is_timer_work(true), m_time(duration_t::zero()), m_begin(clock_t::now()) {};
    ~Timer()
    {
        Print();
    }
    void Stop()
    {
        if (is_timer_work)
        {
            is_timer_work = false;
            m_time += (clock_t::now() - m_begin);
        }
    }
    void Continue()
    {
        if (!is_timer_work)
        {
            is_timer_work = true;
            m_begin = clock_t::now();
        }
    }
    void Reset()
    {
        is_timer_work = true;
        m_time = duration_t::zero();
        m_begin = clock_t::now();

    }
    void Print()
    {
        auto timer_worked = is_timer_work;
        Stop();
      //  std::cout << m_timer_name << " : "<< std::chrono::duration_cast<
       // std::chrono::microseconds> (m_time).count() << " microseconds\n";
        std::cout << std::chrono::duration_cast< std::chrono::microseconds> (m_time).count();

        if (timer_worked)
        {
            Continue();
        }
    }
    long long convert_mil_into_number(){
        return  std::chrono::duration_cast< std::chrono::milliseconds> (m_time).count();
    }
    long long convert_mic_into_number(){
        return  std::chrono::duration_cast< std::chrono::microseconds> (m_time).count();
    }
private:
    const std::string m_timer_name;
    bool is_timer_work;
    duration_t m_time;
    time_point_t m_begin;
};


#endif /* Timer_h */
