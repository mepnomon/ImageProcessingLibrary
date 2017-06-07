/**
********************************************************************************
*
*	@file		Image.cpp
*
*	@brief		Constructor file for the Image class.
*
*	@version	1.0
*
*	@date		25/10/2016
*
*	@author		Dorian B. Dressler (eeu436@bangor@ac.uk)
*
*
********************************************************************************
*/


//******************************************************************************
//	Define
//******************************************************************************
#define LINE_SIZE 2048


//******************************************************************************
//	Include
//******************************************************************************
#include <sstream> // Head file for stringstream
#include <fstream> // Head file for filestream
#include <algorithm>
#include <iostream>

#include "Image.h"

//Constructor
//------------------
Image::Image():
//------------------
        m_width(0),
        m_height(0),
        m_p_image(0)
//------------------
{ // NOTHING TO DO HERE
}

//Copy constructor
//--------------------------------
Image::Image(const Image& anImage):
//--------------------------------
		m_width(anImage.m_width),
		m_height(anImage.m_height),
		m_p_image(new float[m_height*m_width])
//--------------------------------
{
	// IT IS THE CONSTRUCTOR, USE AN INITIALISATION LIST
	// Copies data from one float array to another float array
	std::memcpy(m_p_image, anImage.m_p_image, (m_height*m_width*sizeof(float)));
	
}

//Destructor
//-------------
Image::~Image()
//-------------
{
	delete[] m_p_image;
    // ADD CODE HERE TO RELEASE THE MEMORY
}

//Destructor
//-------------------
void Image::destroy()
//-------------------
{
    // Memory has been dynamically allocated
    if (m_p_image)
    {
        // Release the memory
        delete [] m_p_image;
    
        // Make sure the pointer is reset to NULL
        m_p_image = 0;
    }
    
    // There is no pixel in the image
    m_width  = 0;
    m_height = 0;
}

//Copies the data of an image
//-------------------------------------------
Image& Image::operator=(const Image& anImage)
//-------------------------------------------
{
	// CODE HERE TO COPY THE DATA
	destroy();

	m_width = anImage.m_width;
	m_height = anImage.m_height;
	m_p_image = new float[m_height*m_width];
	std::memcpy(m_p_image, anImage.m_p_image, (m_height*m_width*sizeof(float)));
	return *(this);
}

//Adds two images to each other and returns resulting image
//------------------------------------------
Image Image::operator+(const Image& anImage)
//------------------------------------------
{
	Image tempImage;

	// if original image is smaller than added image
	if (m_width < anImage.m_width) {
		//std::cout << "added image bigger" << std::endl;
		tempImage.m_width = m_width;
		tempImage.m_height = m_height;
		tempImage.m_p_image = new float[m_width*m_height];

		//copy smaller image into temp
		std::memcpy(tempImage.m_p_image, m_p_image, (m_width*m_height * sizeof(float)));

		//itereate over each pixel up to size of smaller image
		for (unsigned int j = 0; j < m_height; ++j) {
			for (unsigned int i = 0; i < m_width; ++i) {
				//add to values in master image' i,j, the values at anImage's i,j and store in temp
				tempImage.m_p_image[j * m_width + i] = m_p_image[j * m_width + i] + anImage.m_p_image[j * anImage.m_width + i];
			}
		}

	}
	else { //if subtracted image equal or smaller
		
		//std::cout << "added image smaller or equal" << std::endl;
		tempImage.m_width = anImage.m_width;
		tempImage.m_height = anImage.m_height;
		tempImage.m_p_image = new float[anImage.m_width*anImage.m_height];
		//copy image pixel by pixel

		//copy original image into temporary image
		std::memcpy(tempImage.m_p_image, anImage.m_p_image, (anImage.m_width*anImage.m_height * sizeof(float)));
		for (unsigned int j = 0; j < anImage.m_height; ++j) {
			for (unsigned int i = 0; i < anImage.m_width; ++i) {
				//still some issues here
				tempImage.m_p_image[j* anImage.m_width + i] = m_p_image[j * m_width + i] + anImage.m_p_image[j* anImage.m_width + i];
				//use couts
			}
		}
	}
	return tempImage;
}


//SUBTRACTS TWO IMAGES FROM EACH OTHER AND RETURNS RESULTING IMAGE
//------------------------------------------
Image Image::operator-(const Image& anImage)
//------------------------------------------
{
	Image tempImage;

	// if original image is smaller than added image
	if (m_width < anImage.m_width) {
		std::cout << "subtracted image bigger" << std::endl;
		tempImage.m_width = m_width;
		tempImage.m_height = m_height;
		tempImage.m_p_image = new float[m_width*m_height];

		//copy smaller image into temp
		std::memcpy(tempImage.m_p_image, m_p_image, (m_width*m_height*sizeof(float)));

		//itereate over each pixel up to size of smaller image
		for (unsigned int j = 0; j < m_height; ++j) {
			for (unsigned int i = 0; i < m_width; ++i) {
				//add to values in master image' i,j, the values at anImage's i,j and store in temp
				tempImage.m_p_image[j * m_width + i] = m_p_image[j * m_width + i] - anImage.m_p_image[j * anImage.m_width + i];
			}
		}

	}
	else { //if subtracted image equal or smaller
		std::cout << "subtracted image smaller or equal" << std::endl;
		tempImage.m_width = anImage.m_width;
		tempImage.m_height = anImage.m_height;
		tempImage.m_p_image = new float[anImage.m_width*anImage.m_height];
		//copy image pixel by pixel

		//copy original image into temporary image
		std::memcpy(tempImage.m_p_image, anImage.m_p_image, (anImage.m_width*anImage.m_height*sizeof(float)));
		
		for (unsigned int j = 0; j < anImage.m_height; ++j) {
			for (unsigned int i = 0; i < anImage.m_width; ++i) {
				tempImage.m_p_image[j* anImage.m_width + i] = m_p_image[j * m_width + i] - anImage.m_p_image[j* anImage.m_width + i];
			}
		}
	}
	return tempImage;
}

//Adds two images and returns a reference to the created image
//--------------------------------------------
Image& Image::operator+=(const Image& anImage)
//--------------------------------------------
{
	unsigned int imageWidth, imageHeight;
	//if anImage is bigger than original image
	if (m_width < anImage.m_width || m_height < anImage.m_height) {

		//set image width and height of smaller image original
		imageWidth = m_width;
		imageHeight = m_height;
	} else { //if anImage is smaller or of equal size than original image
		
		//set image width and height of added image
		imageWidth = anImage.m_width;
		imageHeight = anImage.m_height;
	}

	//iterate rows and columns of pixel array
	for (unsigned int j = 0; j < imageHeight; ++j) {
		for (unsigned int i = 0; i < imageWidth; ++i) {
			
			//add pixels from anImage to image and store in the image
			m_p_image[j* m_width + i] = m_p_image[j * m_width + i] + anImage.m_p_image[j* anImage.m_width + i];
		}
	}
	//return the reference
	return *(this);
}

//Subtracts two images and returns a reference to the image.
//--------------------------------------------
Image& Image::operator-=(const Image& anImage)
//--------------------------------------------
{
	unsigned int imageWidth, imageHeight;
	//set image width and height of smaller image original
	if (m_width < anImage.m_width || m_height < anImage.m_height) {
		//set image width and height to that of original image
		imageWidth = m_width;
		imageHeight = m_height;
	}
	else { //if anImage is smaller or of equal size than original image
		   //set image width and height of added image
			imageWidth = anImage.m_width;
			imageHeight = anImage.m_height;
	}
	//iterate rows and columns of pixel array
	for (unsigned int j = 0; j < imageHeight; ++j) {
		for (unsigned int i = 0; i < imageWidth; ++i) {
			//subtract pixels from anImage to image and store in the image
			m_p_image[j* m_width + i] = m_p_image[j * m_width + i] - anImage.m_p_image[j* anImage.m_width + i];
		}
	}
	//return the reference
	return *(this);
}

//Adds aValue to each pixel of the current image.
//----------------------------------
Image Image::operator+(float aValue)
//----------------------------------
{
	unsigned int pixelsInImage(m_height*m_width);
	Image tempImage;
	tempImage.m_height = m_height;
	tempImage.m_width = m_width;
	tempImage.m_p_image = new float[pixelsInImage];

	//iterate through pixel array
	for (unsigned int i = 0; i < pixelsInImage; ++i) {
		//add value to each value already in array and store at in new image
		tempImage.m_p_image[i] = m_p_image[i] + aValue;
	}
	//returns the new image
	return tempImage;
}

//Subtracts avalue from each pixel of the current image.
//----------------------------------
Image Image::operator-(float aValue)
//----------------------------------
{
	unsigned int pixelsInImage(m_height*m_width);
	Image tempImage;
	tempImage.m_height = m_height;
	tempImage.m_width = m_width;
	tempImage.m_p_image = new float[pixelsInImage];
	
	//iterate through pixel array
	for (unsigned int i = 0; i < pixelsInImage; ++i) {
		//subtracts a value from each value in the original imge and store at in new image
		tempImage.m_p_image[i] = m_p_image[i] - aValue;
	}
	//return the new iamge
	return tempImage;
}

//Multiplies each pixel in image by aValue
//----------------------------------
Image Image::operator*(float aValue)
//----------------------------------
{
	unsigned int pixelsInImage(m_height*m_width);
	Image tempImage; //(new float[pixelsInImage]);
	tempImage.m_height = m_height;
	tempImage.m_width = m_width;
	tempImage.m_p_image = new float[pixelsInImage];
	
	//iterate through pixel array
	for (unsigned int i = 0; i < pixelsInImage; ++i) {
		//multiplies each value in the original with a floating point value and stores it in a new image
		tempImage.m_p_image[i] = m_p_image[i] * aValue;
	}
	//returns the new image
	return tempImage;
}

//Divides each pixel by aValue and returns resulting image
//----------------------------------
Image Image::operator/(float aValue)
//----------------------------------
{
    // ADD CODE HERE TO DIVIDE EACH PIXEL OF THE CURRENT IMAGE BY aValue,
    // AND RETURN THE RESULTING IMAGE
	unsigned int pixelsInImage(m_height*m_width);
	Image tempImage;
	tempImage.m_height = m_height;
	tempImage.m_width = m_width;
	tempImage.m_p_image = new float[pixelsInImage];
	
	for (unsigned int i = 0; i < pixelsInImage; ++i) {
		tempImage.m_p_image[i] = m_p_image[i] / aValue;
	}
	return tempImage;
}

//Arithmetic assignment operator for addition
//-----------------------------------
Image& Image::operator+=(float aValue)
//-----------------------------------
{
	unsigned int pixelsInImage(m_height*m_width);

	//iterates through the pixel array and adds a value to each pixel
	for (unsigned int i = 0; i < pixelsInImage; ++i) {
		m_p_image[i] = m_p_image[i] + aValue;
	}
	//returns the current image
	return *(this);
}

//Assignment operator for subtraction
//------------------------------------
Image& Image::operator-=(float aValue)
//------------------------------------
{
	unsigned int pixelsInImage(m_height*m_width);

	//iterates through each pixel in the array and subtracts a value from it
	for (unsigned int i = 0; i < pixelsInImage; ++i) {
		m_p_image[i] = m_p_image[i] - aValue;
	}
	//returns a reference ot the image
	return *(this);
}

//Assignment operator for multiplication
//------------------------------------
Image& Image::operator*=(float aValue)
//------------------------------------
{
	unsigned int pixelsInImage(m_height*m_width);
	
	//iterates through each pixel in the array and multiplies it with a value
	for (unsigned int i = 0; i < pixelsInImage; ++i) {
		m_p_image[i] = m_p_image[i] * aValue;
	}
	return *(this);
}

//Assignment operator for division
//------------------------------------
Image& Image::operator/=(float aValue)
//------------------------------------
{
	unsigned int pixelsInImage(m_height*m_width);

	//iterates through each pixel in the array and divides it by a value
	for (unsigned int i = 0; i < pixelsInImage; ++i) {
		m_p_image[i] = m_p_image[i] / aValue;
	}
	return *(this);
}

//Implementation of negation operator
//----------------------
Image Image::operator!()
//----------------------
{
	unsigned int pixelsInImage(m_height*m_width);
	const int MAX_COLOR = 255;
	Image tempImage;
	tempImage.m_height = m_height;
	tempImage.m_width = m_width;
	tempImage.m_p_image = new float[pixelsInImage];
	
	//iterates through each pixel in the array and inverts its
	for (unsigned int i = 0; i < pixelsInImage; ++i) {
		tempImage.m_p_image[i] = MAX_COLOR - m_p_image[i];
	}
	return tempImage;
}

//Sets pixel value
//------------------------------
void Image::setPixel(unsigned int i, unsigned int j, float aValue)
//------------------------------
{
	m_p_image[j * m_width + i] = aValue;
}

//Gets pixel value
//------------------------------
float Image::getPixel(unsigned int i, unsigned int j) const
{
	return m_p_image[j * m_width + i];
}
//------------------------------

//Returns max value
//------------------------------
float Image::getMaxValue() const
//------------------------------
{
    return (*std::max_element(&m_p_image[0], &m_p_image[m_width * m_height]));
}

//Returns height
//------------------------------
unsigned int Image::getHeight() const
//------------------------------
{	
	return m_height;
}

//Returns width
//------------------------------
unsigned int Image::getWidth() const
//------------------------------
{
	return m_width;
}

//Displays the aspect ratio
//------------------------------
float Image::getAspectRatio()
{
	float image_ratio = ((float)m_width / (float)m_height);
	return image_ratio;
}


//----------------------------------------------------------------
void Image::shiftScaleFilter(float aShiftValue, float aScaleValue)
//----------------------------------------------------------------
{
    // Process every pixel of the image
    for (unsigned int i = 0; i < m_width * m_height; ++i)
    {
        // Apply the shilft/scale filter
        m_p_image[i] = (m_p_image[i] + aShiftValue) * aScaleValue;
    }
}


//----------------------------------------
void Image::loadPGM(const char* aFileName)
//----------------------------------------
{
    // Open the file
    std::ifstream input_file(aFileName, std::ifstream::binary);
    
    // The file does not exist
    if (!input_file.is_open())
    {
        // Build the error message
        std::stringstream error_message;
        error_message << "Cannot open the file \"" << aFileName << "\". It does not exist";
    
        // Throw an error
        throw (error_message.str());
    }
    // The file is open
    else
    {
        // Release the memory if necessary
        destroy();
    
        // Variable to store a line
        char p_line_data[LINE_SIZE];
    
        // Get the first line
        input_file.getline(p_line_data, LINE_SIZE);

        // Get the image type
        std::string image_type(p_line_data);
    
        // Valid ASCII format
        if (image_type == "P2")
        {
            // Variable to save the max value
            int max_value(-1);
        
            // There is data to read
            unsigned int pixel_count(0);
            while (input_file.good())
            {
                // Get the new line
                input_file.getline(p_line_data, LINE_SIZE);
    
                // It is not a comment
                if (p_line_data[0] != '#')
                {
                    // Store the line in a stream
                    std::stringstream stream_line;
                    stream_line << std::string(p_line_data);
                
                    // The memory is not allocated
                    if (!m_p_image && !m_width && !m_height)
                    {
                        // Load the image size
                        stream_line >> m_width >> m_height;
                    
                        // Alocate the memory
                        m_p_image = new float[m_width * m_height];
                    
                        // Out of memory
                        if (!m_p_image)
                        {
                            throw ("Out of memory");
                        }
                    }
                    // The max value is not set
                    else if (max_value < 0)
                    {
                        // Get the max value;
                        stream_line >> max_value;
                    }
                    // Read the pixel data
                    else
                    {
                        // Process all the pixels of the line
                        while (stream_line.good())
                        {
                            // Get the pixel value
                            int pixel_value(-1);
                            stream_line >> pixel_value;
                            // The pixel exists
                            if (pixel_count < m_width * m_height)
                            {
                                m_p_image[pixel_count++] = pixel_value;
                            }
                        }
                    }
                }
            }
        }
        // Valid binary format
        else if (image_type == "P5")
        {
            // Variable to save the max value
            int max_value(-1);

            // There is data to read
            unsigned int pixel_count(0);
            while (input_file.good() && !pixel_count)
            {
            	// Process as an ASCII file
                if (!m_width || !m_height || max_value < 0)
                {
                    // Get the new line
                    input_file.getline(p_line_data, LINE_SIZE);

                    // It is not a comment
                    if (p_line_data[0] != '#')
                    {
                        // Store the line in a stream
                        std::stringstream stream_line;
                        stream_line << std::string(p_line_data);

                        // The memory is not allocated
                        if (!m_p_image && !m_width && !m_height)
                        {
                            // Load the image size
                            stream_line >> m_width >> m_height;

                            // Allocate the memory
                            m_p_image = new float[m_width * m_height];

                            // Out of memory
                            if (!m_p_image)
                            {
                                throw ("Out of memory");
                            }
                        }
                        // The max value is not set
                        else
                        {
                            // Get the max value;
                            stream_line >> max_value;
                        }
                    }
                }
                // Read the pixel data
                else
                {
                	unsigned char* p_temp(new unsigned char[m_width * m_height]);

                    // Out of memory
                    if (!p_temp)
                    {
                        throw ("Out of memory");
                    }

                    input_file.read(reinterpret_cast<char*>(p_temp), m_width * m_height);

                	for (unsigned int i(0); i < m_width * m_height; ++i)
                	{
						++pixel_count;
                		m_p_image[i] = p_temp[i];
                	}
                	delete [] p_temp;
                }
            }
        }
        // Invalid format
        else
        {
            // Build the error message
            std::stringstream error_message;
            error_message << "Invalid file (\"" << aFileName << "\")";

            // Throw an error
            throw (error_message.str());
        }
    }
}


//-----------------------------------------------
void Image::loadPGM(const std::string& aFileName)
//-----------------------------------------------
{
    loadPGM(aFileName.data());
}


//----------------------------------------
void Image::savePGM(const char* aFileName)
//----------------------------------------
{
    // Open the file
    std::ofstream output_file(aFileName);
    
    // The file does not exist
    if (!output_file.is_open())
    {
        // Build the error message
        std::stringstream error_message;
        error_message << "Cannot create the file \"" << aFileName << "\"";
    
        // Throw an error
        throw (error_message.str());
    }
    // The file is open
    else
    {
        // Set the image type
        output_file << "P2" << std::endl;
    
        // Print a comment
        output_file << "# ICP3038 -- Assignment 1 -- 2015/2016" << std::endl;
    
        // The image size
        output_file << m_width << " " << m_height << std::endl;

        // The get the max value
        output_file << std::min(255, std::max(0, int(getMaxValue()))) << std::endl;
    
        // Process every line
        for (unsigned int j = 0; j < m_height; ++j)
        {
            // Process every column
            for (unsigned int i = 0; i < m_width; ++i)
            {
                // Process the pixel
                int pixel_value(m_p_image[j * m_width + i]);
                pixel_value = std::max(0, pixel_value);
                pixel_value = std::min(255, pixel_value);
            
                output_file << pixel_value;
            
                // It is not the last pixel of the line
                if (i < (m_width - 1))
                {
                    output_file << " ";
                }
            }
        
            // It is not the last line of the image
            if (j < (m_height - 1))
            {
                output_file << std::endl;
            }
        }
    }
}


//-----------------------------------------------
void Image::savePGM(const std::string& aFileName)
//-----------------------------------------------
{
    savePGM(aFileName.data());
}
