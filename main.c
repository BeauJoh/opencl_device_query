#include <stdio.h>
#include <math.h>
#include <sys/time.h>

//OpenCL header files
#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.h>
#else
//if Linux
#include <CL/cl.h>
#endif

int main(int argc, char** argv)
{
    cl_uint number_of_platforms = 0;
    clGetPlatformIDs((cl_uint)NULL,        //num_entries
            NULL,                 //platforms
            &number_of_platforms);//num_platforms
    if(number_of_platforms==0){
        printf("Error: No platforms found!\n");
        printf("\tIs an OpenCL driver installed?");
        return EXIT_FAILURE;
    }

    //get all those platforms
    cl_platform_id* my_platforms =
        (cl_platform_id*)malloc(sizeof(cl_platform_id)*
                number_of_platforms);
    clGetPlatformIDs(number_of_platforms,//num_entries
            my_platforms,       //platform
            NULL);              //num_platforms

    printf("\n");
    printf("Your system platform id(s) are:\n");
    //print some details about each platform
    for(size_t i = 0; i < number_of_platforms; i++){
        printf("\tplatform no. %lu\n",i);

        //print it's name
        size_t total_buffer_length = 1024;
        size_t length_of_buffer_used = 0;
        char my_platform_name[total_buffer_length];
        clGetPlatformInfo(my_platforms[i],        //platform
                CL_PLATFORM_NAME,       //param_name
                total_buffer_length,    //param_value_size
                &my_platform_name,      //param_value
                &length_of_buffer_used);//param_value_size_ret
        printf("\t\tname:\t\t%*.*s\n",(int)length_of_buffer_used,
                (int)length_of_buffer_used,my_platform_name);

        //print the vendor
        char my_platform_vendor[total_buffer_length];
        length_of_buffer_used = 0;
        clGetPlatformInfo(my_platforms[i],        //platform
                CL_PLATFORM_VENDOR,     //param_name
                total_buffer_length,    //param_value_size
                &my_platform_vendor,    //param_value
                &length_of_buffer_used);//param_value_size_ret
        printf("\t\tvendor:\t\t%*.*s\n",(int)length_of_buffer_used,
                (int)length_of_buffer_used,my_platform_vendor);

        //print the profile
        char my_platform_profile[total_buffer_length];
        length_of_buffer_used = 0;
        clGetPlatformInfo(my_platforms[i],        //platform
                CL_PLATFORM_PROFILE,    //param_name
                total_buffer_length,    //param_value_size
                &my_platform_profile,   //param_value
                &length_of_buffer_used);//param_value_size_ret
        printf("\t\tprofile:\t%*.*s\n",(int)length_of_buffer_used,
                (int)length_of_buffer_used,my_platform_profile);

        //print the extensions
        char my_platform_extensions[total_buffer_length];
        length_of_buffer_used = 0;
        clGetPlatformInfo(my_platforms[i],        //platform
                CL_PLATFORM_EXTENSIONS, //param_name
                total_buffer_length,    //param_value_size
                &my_platform_extensions,//param_value
                &length_of_buffer_used);//param_value_size_ret
        printf("\t\textensions:\t%*.*s\n",(int)length_of_buffer_used,
                (int)length_of_buffer_used,my_platform_extensions);

        //given this platform, how many devices are available?
        //start by getting the count of available devices
        cl_uint number_of_devices = 0;
        clGetDeviceIDs(my_platforms[i],    //platform_id
                CL_DEVICE_TYPE_ALL, //device_type
                (cl_uint)NULL,      //num_entries
                NULL,               //devices
                &number_of_devices);//num_devices
        if(number_of_devices==0){
            printf("Error: No devices found for this platform!\n");
            return EXIT_FAILURE;
        }
        printf("\n\t\twith device id(s):\n");

        //get all those platforms
        cl_device_id* my_devices =
            (cl_device_id*)malloc(sizeof(cl_device_id)*number_of_devices);
        clGetDeviceIDs(my_platforms[i],    //platform_id
                CL_DEVICE_TYPE_ALL, //device_type
                number_of_devices,  //num_entries
                my_devices,         //devices
                NULL);              //num_devices
        //for each device print some of its details:
        for(size_t j = 0; j < number_of_devices; j++){
            printf("\t\tdevice no. %lu\n",j);

            //print the name
            char my_device_name[total_buffer_length];
            length_of_buffer_used = 0;
            clGetDeviceInfo(my_devices[j],          //device
                    CL_DEVICE_NAME,         //param_name
                    total_buffer_length,    //param_value_size
                    &my_device_name,        //param_value
                    &length_of_buffer_used);//param_value_size_ret
            printf("\t\t\tname:\t\t%*.*s\n",(int)length_of_buffer_used,
                    (int)length_of_buffer_used,my_device_name);

            //print the vendor
            char my_device_vendor[total_buffer_length];
            length_of_buffer_used = 0;
            clGetDeviceInfo(my_devices[i],          //device
                    CL_DEVICE_VENDOR,       //param_name
                    total_buffer_length,    //param_value_size
                    &my_device_vendor,      //param_value
                    &length_of_buffer_used);//param_value_size_ret
            printf("\t\t\tvendor:\t\t%*.*s\n\n",(int)length_of_buffer_used,
                    (int)length_of_buffer_used,my_device_vendor);
        }
        printf("\n");
        free(my_devices);
    } 

    free(my_platforms);
    return EXIT_SUCCESS;
}

