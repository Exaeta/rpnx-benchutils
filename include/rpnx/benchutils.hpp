#ifndef RPNX_BENCHUTILS_HH
#define RPNX_BENCHUTILS_HH
#include <chrono>
#include <string>
#include <sstream>

namespace rpnx
{
  template <typename F>
  auto time_call(F&&f) -> std::chrono::high_resolution_clock::duration
  {
    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();
    f();
    auto t2 = high_resolution_clock::now();

    return t2-t1;
  }
  
  inline std::string bytespeed(std::chrono::high_resolution_clock::duration const & am, size_t bytes)
  {
    using namespace std;
    std::stringstream ss;
    ss.imbue(std::locale::classic());
    
    size_t cbytes = (1s/am)*bytes;
    
    if (cbytes < (size_t(1) << 10)) 
    {
      ss << cbytes << " B/s";
      return ss.str();
    }
    
    if (cbytes < (size_t(1)  << 20 ))
    {
      ss << double(cbytes)/(size_t(1) << 10) << " KiB/s";
      return ss.str();
    }
    
    if (cbytes < (size_t(1)  << 30 ))
    {
      ss << double(cbytes)/(size_t(1) << 20) << " MiB/s";
      return ss.str();
    }
    
    if (cbytes < (size_t(1)  << 40 ))
    {
      ss << double(cbytes)/(size_t(1) << 30) << " GiB/s";
      return ss.str();
    }
    
    if (cbytes < (size_t(1)  << 50 ))
    {
      ss << double(cbytes)/(size_t(1) << 40) << " TiB/s";
      return ss.str();
    }
    
    return "??? B/s";
    
  }
  
  inline std::string time_to_english(std::chrono::high_resolution_clock::duration const & am)
  {
    using namespace std;
    using namespace std::chrono;
    using namespace std::chrono_literals;
    
    std::stringstream ss;
    ss.imbue(std::locale::classic());
    
    if (am < (1us))
    {
        ss << am.count() << "ns";
        return ss.str();
    } else if (am < (1ms))
    {
        ss << static_cast<double>(am.count())/1000 << "us";
        return ss.str();
    } else if (am < seconds(1))
    {
        ss << static_cast<double>(am.count())/1000/1000 << "ms";
        return ss.str();
    }
    ss << static_cast<double>(am.count())/1000/1000/1000 << "s";
    return ss.str();
  }
  
  template <typename F>
  auto benchmark_once(std::ostream & os, std::string const & name, F && f)
  {
    auto l = time_call(f);
    os << "Benchmark '" << name << "' took " << time_to_english(l) << std::endl;
    return l;
  }
  
  template <typename F, typename S>
  auto benchmark_once(std::ostream & os, std::string const & name, F && f, S && s)
  {
    using namespace std::chrono_literals;
    auto l = time_call(f);
    size_t ss  = s();
    os << "Benchmark '" << name << "' took " << time_to_english(l) << " ("<< bytespeed(l, ss) <<")" << std::endl;
    return l;
  }


  
}
#endif
