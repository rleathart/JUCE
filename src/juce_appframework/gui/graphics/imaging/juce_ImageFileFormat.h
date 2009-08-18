/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-9 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_IMAGEFILEFORMAT_JUCEHEADER__
#define __JUCE_IMAGEFILEFORMAT_JUCEHEADER__

#include "juce_Image.h"
#include "../../../../juce_core/io/files/juce_File.h"
#include "../../../../juce_core/io/juce_InputStream.h"
#include "../../../../juce_core/io/juce_OutputStream.h"


//==============================================================================
/**
    Base-class for codecs that can read and write image file formats such
    as PNG, JPEG, etc.

    This class also contains static methods to make it easy to load images
    from files, streams or from memory.

    @see Image, ImageCache
*/
class JUCE_API  ImageFileFormat
{
protected:
    //==============================================================================
    /** Creates an ImageFormat. */
    ImageFileFormat() throw()           {}

public:
    /** Destructor. */
    virtual ~ImageFileFormat() throw()  {}

    //==============================================================================
    /** Returns a description of this file format.

        E.g. "JPEG", "PNG"
    */
    virtual const String getFormatName() = 0;

    /** Returns true if the given stream seems to contain data that this format
        understands.

        The format class should only read the first few bytes of the stream and sniff
        for header bytes that it understands.

        @see decodeImage
    */
    virtual bool canUnderstand (InputStream& input) = 0;

    /** Tries to decode and return an image from the given stream.

        This will be called for an image format after calling its canUnderStand() method
        to see if it can handle the stream.

        @param input    the stream to read the data from. The stream will be positioned
                        at the start of the image data (but this may not necessarily
                        be position 0)
        @returns        the image that was decoded, or 0 if it fails. It's the
                        caller's responsibility to delete this image when no longer needed.
        @see loadFrom
    */
    virtual Image* decodeImage (InputStream& input) = 0;

    //==============================================================================
    /** Attempts to write an image to a stream.

        To specify extra information like encoding quality, there will be appropriate parameters
        in the subclasses of the specific file types.

        @returns        true if it nothing went wrong.
    */
    virtual bool writeImageToStream (const Image& sourceImage,
                                     OutputStream& destStream) = 0;

    //==============================================================================
    /** Tries the built-in decoders to see if it can find one to read this stream.

        There are currently built-in decoders for PNG, JPEG and GIF formats.

        The object that is returned should not be deleted by the caller.

        @see canUnderstand, decodeImage, loadFrom
    */
    static ImageFileFormat* findImageFormatForStream (InputStream& input);

    //==============================================================================
    /** Tries to load an image from a stream.

        This will use the findImageFormatForStream() method to locate a suitable
        codec, and use that to load the image.

        @returns  the image that was decoded, or 0 if it fails to load one. It's the
                  caller's responsibility to delete this image when no longer needed.
    */
    static Image* loadFrom (InputStream& input);

    /** Tries to load an image from a file.

        This will use the findImageFormatForStream() method to locate a suitable
        codec, and use that to load the image.

        @returns  the image that was decoded, or 0 if it fails to load one. It's the
                  caller's responsibility to delete this image when no longer needed.
    */
    static Image* loadFrom (const File& file);

    /** Tries to load an image from a block of raw image data.

        This will use the findImageFormatForStream() method to locate a suitable
        codec, and use that to load the image.

        @returns  the image that was decoded, or 0 if it fails to load one. It's the
                  caller's responsibility to delete this image when no longer needed.
    */
    static Image* loadFrom (const void* rawData,
                            const int numBytesOfData);

};

//==============================================================================
/**
    A type of ImageFileFormat for reading and writing PNG files.

    @see ImageFileFormat, JPEGImageFormat
*/
class JUCE_API  PNGImageFormat  : public ImageFileFormat
{
public:
    //==============================================================================
    PNGImageFormat() throw();
    ~PNGImageFormat() throw();

    //==============================================================================
    const String getFormatName();
    bool canUnderstand (InputStream& input);

    Image* decodeImage (InputStream& input);

    bool writeImageToStream (const Image& sourceImage, OutputStream& destStream);
};


//==============================================================================
/**
    A type of ImageFileFormat for reading and writing JPEG files.

    @see ImageFileFormat, PNGImageFormat
*/
class JUCE_API  JPEGImageFormat  : public ImageFileFormat
{
public:
    //==============================================================================
    JPEGImageFormat() throw();
    ~JPEGImageFormat() throw();

    //==============================================================================
    /** Specifies the quality to be used when writing a JPEG file.

        @param newQuality  a value 0 to 1.0, where 0 is low quality, 1.0 is best, or
                           any negative value is "default" quality
    */
    void setQuality (const float newQuality);

    //==============================================================================
    const String getFormatName();

    bool canUnderstand (InputStream& input);

    Image* decodeImage (InputStream& input);

    bool writeImageToStream (const Image& sourceImage, OutputStream& destStream);

private:
    float quality;
};



#endif   // __JUCE_IMAGEFILEFORMAT_JUCEHEADER__
