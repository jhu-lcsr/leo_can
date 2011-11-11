
#include <sawCANBus/osaRTSocketCAN.h>
#include <native/task.h>
#include <sys/mman.h>

int main( int argc, char** argv ){

  mlockall(MCL_CURRENT | MCL_FUTURE);
  RT_TASK task;
  rt_task_shadow( &task, "RTSocketCANRecv", 1, 0);

  cmnLogger::SetMask( CMN_LOG_ALLOW_ALL );
  cmnLogger::SetMaskFunction( CMN_LOG_ALLOW_ALL );
  cmnLogger::SetMaskDefaultLog( CMN_LOG_ALLOW_ALL );

  if( argc != 2 ){
    std::cerr << "Usage: " << argv[0] << " rtcan[?]" << std::endl;
    return -1;
  }

  osaRTSocketCAN can( argv[1], osaCANBus::RATE_1000 );

  if( can.Open() != osaCANBus::ESUCCESS ){
    std::cerr << argv[0] << ": Failed to open device " << argv[1] << std::endl;
    return -1;
  }

  osaCANBusFrame frame;
  
  if( can.Recv( frame ) != osaCANBus::ESUCCESS ){
    std::cerr << argv[0] << ": Failed to recv: " << argv[1] << std::endl;
    return -1;
  }

  std::cout << frame << std::endl;

  if( can.Close() != osaCANBus::ESUCCESS ){
    std::cerr << argv[0] << ": Failed to close device " << argv[1] << std::endl;
    return -1;
  }


  return 0;
}
