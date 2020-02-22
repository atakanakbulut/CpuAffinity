#include <iostream>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <sched.h>
#include <stdio.h>

void helper()
{
   printf("--help Show command list\n");
   printf("--memory-leak : create memory leak \n");
   printf("--cpu-leak cpunumber : 100 cpu usage \n");
}

void createMemoryLeak()
{
   std::cout << "memory leak function.." << std::endl;

   for(;;)
   {
     char *ch = new char[1024];
   }
}

void singleCoreThread()
{
   std::cout << "single core cpu peak" << std::endl;

   for(;;)
   {
      // std::cout << "CORE: " << sched_getcpu() << std::endl;
   }
}

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
       helper();
       exit(0);
    }
    else if(argc == 2 && std::string(argv[1]) == "--memory-leak")
    {
       std::cout << "creating memory leak " << std::endl;
       createMemoryLeak();
    }
    else if(argc == 3 && std::string(argv[1]) == "--cpu-leak" && (  std::string(argv[2]) == "1" ||
                                                                    std::string(argv[2]) == "2" || 
                                                                    std::string(argv[2]) == "3" || 
                                                                    std::string(argv[2]) == "4"))
    {
   
    std::thread th(singleCoreThread);

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    int core_id = std::stoi(std::string(argv[2]).c_str());
    CPU_SET(core_id, &cpuset); // core_id atamak istediginiz core' un idsi

    pthread_setaffinity_np(th.native_handle(), sizeof(cpu_set_t), &cpuset);
    th.join();

    }
    else
    {
        helper();
        exit(0);
    }
    
    return 0;
}