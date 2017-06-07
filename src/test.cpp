/**
********************************************************************************
*
*	@file		test.cpp
*
*	@brief		TESTER FOR IMAGE CLASS
*
*	@version	1.0
*
*	@date		25/10/2016
*
*	@author		Dorian B. Dressler
*
*
********************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include <sstream>
#include <iostream>
#include <exception>

#include "Image.h"


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    // Return code
    int error_code(0);
    
    // Catch exceptions
    try
    {
        // Good number of arguments
        if (argc == 3)//prev 3
        {
            // Load an image
            Image test_image;
			Image test_image2;
			//Image test_image2;
            test_image.loadPGM(argv[1]);
			//test_image2.loadPGM(argv[2]);
			// Save the image
			char* fileName = (argv[2]);
            //test_image.savePGM(argv[3]);
			
			Image test_image3;
			std::cout << test_image.getAspectRatio() << std::endl;
			//std::cout << test_image.getHeight() << std::endl;
			//std::cout << test_image.getWidth() << std::endl;
			//std::cout << test_image.getPixel(25, 25) << std::endl;
			//test_image.setPixel(25, 25, 125);
			//test_image.savePGM(fileName);
			//std::cout << test_image.getPixel(25, 25) << std::endl;

			//std::cout << test_image.getAspectRatio() << std::endl;
			//test_image3 = test_image / (2.5);
			//test_image3.savePGM(fileName);
			//(!(test_image)).savePGM(fileName);
			//test_image3.savePGM(fileName);
			//(!(test_image)).savePGM("test.pgm");
			//Create second image to perform tests on
			//Image test_image3(test_image);

			/*std::cout << test_image3.getPixel(25, 25) << std::endl;
			test_image3.setPixel(25, 25, 100);
			std::cout << test_image3.getPixel(25, 25) << std::endl;
			test_image3.savePGM("Result.pgm");*/
			//(test_image -= (test_image2)).savePGM("Result.pgm");
			//(!(test_image)).savePGM("result.pgm");
			//test_image2 = test_image + (100.0);
			//test_image3.savePGM("ResultThree.pgm");

			//Image test_image3;
			//test_image3 = test_image+(test_image2);
			//test_image3.savePGM("result.pgm");
			//----------------------
			//testing plus operator again
			//test_image3 = test_image / (100.0);
			//test_image3 = test_image /= (50.0);
			//-----------------------
			//testing + operator
			//test_img2 = test_image + (100);
			//test_img2.savePGM("+operator_test.pgm");
			//(!(test_image)).savePGM("result.pgm");
			//test_image3.savePGM("result.pgm");
			
			//Image test_img3;
			//test_img2 = test_image - (100);
			//test_img3 = test_img2 -= (test_image);
			//Image = test_image += (test_image);
			//test_img2 -= (100);
			
			//-------------------------
			//Testing ! operator
			//(!test_image).savePGM("test3.pgm");
			//test_img2 = !(test_image);
			//test_img2.savePGM("test4.pgm");


        }
        // Wrong number of argument
        else
        {
            // Build the error message
            std::stringstream error_message;
            error_message << "Wrong number of arguments, usage:" << std::endl;
            error_message << "\t" << argv[0] << " input_file_name.pgm output_file_name.pgm" << std::endl;
        
            // Throw the error
            throw (error_message.str());
        }
    }
    // An error occured
    catch (const std::exception& error)
    {
        error_code = 1;
        std::cerr << error.what() << std::endl;
    }
    catch (const std::string& error)
    {
        error_code = 1;
        std::cerr << error << std::endl;
    }
    catch (const char* error)
    {
        error_code = 1;
        std::cerr << error << std::endl;
    }
    catch (...)
    {
        error_code = 1;
        std::cerr << "Unknown error" << std::endl;
    }

    return (error_code);
}
