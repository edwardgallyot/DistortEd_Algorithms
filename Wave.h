//
// Created by Edward Gallyot on 03/01/2022.
//

#ifndef WAVE_IO_WAVE_H
#define WAVE_IO_WAVE_H

#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <functional>

class WaveHeader
{
public:
    WaveHeader () = default;

    ~WaveHeader () = default;

    void getHeader (std::fstream& fstream);

    void writeHeader (std::fstream& fstream);

    void setSamplesPerSec (uint32_t p_samplesPerSec)
    { samplesPerSec = p_samplesPerSec; }

    void setBytesPerSec (uint32_t p_bytesPerSec)
    { WaveHeader::bytesPerSec = p_bytesPerSec; }

    uint32_t getSubchunk2Size () const
    { return Subchunk2Size; }

    size_t getHeaderSize () const
    { return m_size; }

    void printInfo ();

    void setBlockAlign (uint16_t blockAlign);

    void setChunkSize (uint32_t chunkSize);

    void setNumOfChan (uint16_t numOfChan);

    uint16_t getNumOfChan () const;

    uint32_t getSamplesPerSec () const;

    void setSubchunk2Size (uint32_t subchunk2Size);

    void setBitsPerSample (uint16_t bitsPerSample);

    uint16_t getBitsPerSample () const;

private:
    static void printHead (char* head);

    /* RIFF Chunk Descriptor */
    char RIFF[4] {}; // RIFF Header Magic Header
    uint32_t chunkSize {};

    // RIFF Chunk Size
    char WAVE[4] {}; // WAVE Header

    /* "fmt" sub-chunk */
    char fmt[4] {}; // FMT m_headerIn
    uint32_t subchunk1Size {}; // Size of the fmt chunk
    uint16_t audioFormat {}; // Audio Format 1=PCM, 6=mulaw, 7=a-law
    uint16_t numOfChan {}; // Number of channels


    uint32_t samplesPerSec {};// Sample Rate

    uint32_t bytesPerSec {}; // bytes per second
    uint16_t blockAlign {};
public:
    uint16_t getBlockAlign () const;
private:
    // 2=16-bit mono, 4=16-bit stereo

    uint16_t bitsPerSample {};


    /* m_byteData sub-chunk */
    char Subchunk2ID[4] {}; // "m_byteData" string

    // Sampled data length
    uint32_t Subchunk2Size {};


    // WAV Header is always 44 bytes
    size_t m_size {44};
};

void WaveHeader::getHeader (std::fstream& fstream)
{
    fstream.read (reinterpret_cast<char*>(RIFF), 4);
    fstream.read (reinterpret_cast<char*>(&chunkSize), 4);
    fstream.read (reinterpret_cast<char*>(WAVE), 4);
    fstream.read (reinterpret_cast<char*>(fmt), 4);
    fstream.read (reinterpret_cast<char*>(&subchunk1Size), 4);
    fstream.read (reinterpret_cast<char*>(&audioFormat), 2);
    fstream.read (reinterpret_cast<char*>(&numOfChan), 2);
    fstream.read (reinterpret_cast<char*>(&samplesPerSec), 4);
    fstream.read (reinterpret_cast<char*>(&bytesPerSec), 4);
    fstream.read (reinterpret_cast<char*>(&blockAlign), 2);
    fstream.read (reinterpret_cast<char*>(&bitsPerSample), 2);
    fstream.read (reinterpret_cast<char*>(Subchunk2ID), 4);
    fstream.read (reinterpret_cast<char*>(&Subchunk2Size), 4);
};

void WaveHeader::writeHeader (std::fstream& fstream)
{
    fstream.write (reinterpret_cast<char*>(RIFF), 4);
    fstream.write (reinterpret_cast<char*>(&chunkSize), 4);
    fstream.write (reinterpret_cast<char*>(WAVE), 4);
    fstream.write (reinterpret_cast<char*>(fmt), 4);
    fstream.write (reinterpret_cast<char*>(&subchunk1Size), 4);
    fstream.write (reinterpret_cast<char*>(&audioFormat), 2);
    fstream.write (reinterpret_cast<char*>(&numOfChan), 2);
    fstream.write (reinterpret_cast<char*>(&samplesPerSec), 4);
    fstream.write (reinterpret_cast<char*>(&bytesPerSec), 4);
    fstream.write (reinterpret_cast<char*>(&blockAlign), 2);
    fstream.write (reinterpret_cast<char*>(&bitsPerSample), 2);
    fstream.write (reinterpret_cast<char*>(Subchunk2ID), 4);
    fstream.write (reinterpret_cast<char*>(&Subchunk2Size), 4);
};

void WaveHeader::printInfo ()
{
    std::cout << std::endl;
    printHead (RIFF);
    std::cout << "File Size: " << chunkSize << std::endl;
    std::cout << std::endl;
    printHead (WAVE);
    printHead (fmt);
    std::cout << "Chunk 1 Size: " << subchunk1Size << std::endl;
    std::cout << "Channels: " << numOfChan << std::endl;
    std::cout << "Sample Rate: " << samplesPerSec << std::endl;
    std::cout << "Byte Rate: " << bytesPerSec << std::endl;
    std::cout << "Bits Per Sample: " << bitsPerSample << std::endl;
    std::cout << std::endl;
    printHead (Subchunk2ID);
    std::cout << "Size: " << Subchunk2Size << std::endl;
};

void WaveHeader::printHead (char* head)
{
    for (auto i = 0; i < 4; i++)
        std::cout << head[i];
    std::cout << ": " << std::endl;
}

uint32_t WaveHeader::getSamplesPerSec () const
{
    return samplesPerSec;
}

void WaveHeader::setSubchunk2Size (uint32_t subchunk2Size)
{
    Subchunk2Size = subchunk2Size;
}

uint16_t WaveHeader::getNumOfChan () const
{
    return numOfChan;
}

void WaveHeader::setNumOfChan (uint16_t numOfChan)
{
    WaveHeader::numOfChan = numOfChan;
}

void WaveHeader::setBlockAlign (uint16_t blockAlign)
{
    WaveHeader::blockAlign = blockAlign;
}

void WaveHeader::setChunkSize (uint32_t chunkSize)
{
    WaveHeader::chunkSize = chunkSize;
}

void WaveHeader::setBitsPerSample (uint16_t bitsPerSample)
{
    WaveHeader::bitsPerSample = bitsPerSample;
}

uint16_t WaveHeader::getBitsPerSample () const
{
    return bitsPerSample;
}
uint16_t WaveHeader::getBlockAlign () const
{
    return blockAlign;
};


template<typename T>
class Wave : public WaveHeader
{
public:
    Wave () = default;

    ~Wave ()
    {
        delete m_fileName;
        for (auto channel = 0; channel < getNumOfChan (); ++channel)
        {

        }
        delete[] m_Data;
        delete[] m_byteData;
    };

    void printFileName ()
    { std::cout << *m_fileName << ": " << std::endl; }

    void readFile (std::string fileName)
    {
        setFileName (fileName);
        readData ();
    };

    void writeFile (std::string fileName)
    {
        setFileName (fileName);
        writeData ();
    };

    void processData (std::function<T(T, float)> function, float coeff1);
    void processData (std::function<T(T)> function);

    void writeFileWithMute (std::string fileName)
    {
        setFileName (fileName);
        writeDataWithMute ();
    };

    void writeFileWithNewSampleRate (std::string fileName, uint32_t rate)
    {
        setFileName (fileName);
        writeDataWithNewSampleRate (rate);
    };

    void writeFileWithBitRate (std::string fileName, uint32_t rate)
    {
        setFileName (fileName);
        writeDataWithBitRate (rate);
    };

    void clearFileName ()
    { delete m_fileName; };

private:

    void writeDataWithBitRate (uint32_t rate);

    void changeSampleRate (uint32_t rate)
    {
        setSamplesPerSec (rate);
        setBytesPerSec (2 * rate);
    }

    void checkFileStream ()
    {
        if (!m_fileStream.is_open ())
            throw std::runtime_error ("File Stream Failed to Open");
    }

    void checkFileName ()
    {
        if (m_fileName == nullptr)
            throw std::runtime_error ("File Name Is Not Set");
    }

    void readHeader ();

    void setFileName (const std::string& fileName)
    {
        if (m_fileName == nullptr)
            m_fileName = new std::string {fileName};
        else
            *m_fileName = fileName;
    }

    void readData ();

    void writeData ();

    int16_t getLittleEndianInt (int i, int8_t*& byteData) const
    {
        // Bitwise or is the same as adding two byte values together
        // In a 16 bit integer if we shift the second byte to be first we have a little endian byte form.
        // If we were on a big endian machine we sould swap the two terms either side of bitwise or around
        auto sample_i = static_cast<int16_t>((byteData[i] & 0xff) | (byteData[i + 1] << 8));
        return sample_i;
    };

    void writeDataWithMute ();

    void writeDataWithNewSampleRate (uint32_t newRate);

    std::string* m_fileName {nullptr};
    std::fstream m_fileStream;
    int8_t* m_byteData {nullptr};
    size_t m_byteLength {0};
    T** m_Data {nullptr};
    size_t m_dataLength {0};
};

template<typename T>
void Wave<T>::readData ()
{
    readHeader ();
    checkFileName ();
    m_byteData = new int8_t[m_byteLength];
    m_fileStream.open (*m_fileName, std::ios::in | std::ios_base::binary);
    checkFileStream ();
    m_fileStream.seekg (getHeaderSize (), std::ios::beg);
    m_fileStream.read (reinterpret_cast<char*>(m_byteData), m_byteLength);
    m_fileStream.close ();

    // Allocate the data for the number of channels
    auto numOfChannels = getNumOfChan ();
    auto dataSize = getSubchunk2Size () / (getBitsPerSample () / 8);
    auto channelSize = dataSize / numOfChannels;
    auto bytesPerBlock = getBlockAlign ();

    m_Data = new T* [numOfChannels];
    // Programatically Allocate the number of channels
    for (auto channel = 0; channel < numOfChannels; ++channel)
    {
        m_Data[channel] = new T[channelSize];
    }

    for (auto byte = 0; byte < m_byteLength; byte += bytesPerBlock)
    {
        for (auto channel = 0; channel < numOfChannels; ++channel)
        {
            auto bytePosition = byte + (channel * (bytesPerBlock / numOfChannels));
            auto dataPosition = byte / bytesPerBlock;
            auto sample_i = getLittleEndianInt (bytePosition, m_byteData);
            T sample_f = sample_i / static_cast<T>(std::numeric_limits<int16_t>::max ());
            m_Data[channel][dataPosition] = sample_f;
        }
    }
}

template<typename T>
void Wave<T>::processData (std::function<T(T, float)> function, float coeff1)
{
    auto numOfChannels = getNumOfChan ();
    auto dataSize = getSubchunk2Size () / (getBitsPerSample () / 8);
    auto channelSize = dataSize / numOfChannels;
    for (auto dataPosition = 0; dataPosition < channelSize; ++dataPosition)
    {
        for (auto channel = 0; channel < numOfChannels; ++channel)
        {
            auto sample = m_Data[channel][dataPosition];
            //std::cout << m_Data[channel][dataPosition] << std::endl;
            m_Data[channel][dataPosition] = function(sample, coeff1);
        }
    }
}

template<typename T>
void Wave<T>::processData (std::function<T(T)> function)
{
    auto numOfChannels = getNumOfChan ();
    auto dataSize = getSubchunk2Size () / (getBitsPerSample () / 8);
    auto channelSize = dataSize / numOfChannels;
    for (auto dataPosition = 0; dataPosition < channelSize; ++dataPosition)
    {
        for (auto channel = 0; channel < numOfChannels; ++channel)
        {
            auto sample = m_Data[channel][dataPosition];
            m_Data[channel][dataPosition] = function(sample);
        }
    }
}

template<typename T>
void Wave<T>::writeData ()
{
    // Check there is a file name
    checkFileName ();
    // Open up and check the file stream
    m_fileStream.open (*m_fileName, std::ios::out | std::ios::binary);
    checkFileStream ();
    // Write the m_headerIn of the file
    writeHeader (m_fileStream);

    auto numOfChannels = getNumOfChan ();

    auto dataSize = getSubchunk2Size () / (getBitsPerSample () / 8);
    auto channelSize = dataSize / numOfChannels;
    auto bytesPerBlock = getBlockAlign ();

    for (auto dataPosition = 0; dataPosition < channelSize; ++dataPosition)
    {
        for (auto channel = 0; channel < numOfChannels; ++channel)
        {
            int16_t littleEndianValue = std::numeric_limits<int16_t>::max () * m_Data[channel][dataPosition];
            m_fileStream.write (reinterpret_cast<char*>(&littleEndianValue), 2);
        }
    }

    m_fileStream.close (); // Close the file stream
}

template<typename T>
void Wave<T>::writeDataWithMute ()
{
    // Check there is a file name
    // Open up the File Stream
    checkFileName ();
    m_fileStream.open (*m_fileName, std::ios::out | std::ios::binary);
    checkFileStream ();
    // Write the header to the file
    writeHeader (m_fileStream);
    for (int i = 0; i < m_dataLength; i++)
    {
        int16_t littleEndianValue;
        // Get the value from out data array
        // If inside d_T
        if (i >= ((m_dataLength / 2) + (m_dataLength / 100))
            && i <= ((m_dataLength / 2) + (m_dataLength / 30)))
            littleEndianValue = 0;
        else
            littleEndianValue = std::numeric_limits<int16_t>::max () * m_Data[i];
        // Create a byte Array to write to the file
        m_fileStream.write (reinterpret_cast<char*>(&littleEndianValue), 2);
    }
    m_fileStream.close ();
}

template<typename T>
void Wave<T>::writeDataWithBitRate (uint32_t rate)
{
    checkFileName ();
    m_fileStream.open (*m_fileName, std::ios::out | std::ios::binary);
    checkFileStream ();
    auto bytesPerSample = rate / 8;
    auto samplesPerFrame = getNumOfChan ();
    auto oldDataLength = getSubchunk2Size ();
    auto oldBitRate = getBitsPerSample ();
    auto sizeMultiplier = static_cast<float>(rate) / oldBitRate;
    auto newSubChunkSize = getSubchunk2Size () * sizeMultiplier;
    setChunkSize (36 + (1 * bytesPerSample * getNumOfChan ()));
    setBytesPerSec (getSamplesPerSec () * getNumOfChan () * bytesPerSample);
    setBlockAlign (bytesPerSample * getNumOfChan ());
    setBitsPerSample (bytesPerSample * 8);
    setSubchunk2Size (newSubChunkSize);
    writeHeader (m_fileStream);

    auto increment = (getBitsPerSample () / 8) * getNumOfChan ();

    T* oldData = m_Data;
    auto newDataLength = getSubchunk2Size ();
    T* newData = new T[newDataLength];

    for (auto i = 0; i < newDataLength - 1; ++i)
    {
        newData[i] = oldData[i * 2];
    }

    m_Data = newData;

    writeData ();
}

template<typename T>
void Wave<T>::writeDataWithNewSampleRate (uint32_t newRate)
{
    // Calculate Sizes of data at new sample rate
    auto fileSizeOverOriginalRate = static_cast<double>(getSubchunk2Size () / getSamplesPerSec ());
    auto newChunkSize = static_cast<unsigned long>(newRate * fileSizeOverOriginalRate);
    auto newDataLength = newChunkSize / 2;

    // Build a new set of data
    auto* newData = new T[newDataLength];
    for (int i = 0; i < newDataLength; i++)
    {
        auto new_index = ((float) i / (float) newChunkSize) * getSubchunk2Size ();
        auto index0 = static_cast<unsigned int>(new_index);
        auto index1 = index0 + 1;
        auto value0 = m_Data[index0];
        auto value1 = m_Data[index1];
        auto frac = new_index - (float) index0;
        T currentSample = value0 + frac * (value1 - value0);
        newData[i] = currentSample;
    }

    // Store the old values before writing
    T* old_data = m_Data;
    m_Data = newData;
    auto oldSampleRate = getSamplesPerSec ();
    changeSampleRate (newRate);
    auto oldSubChunkSize = getSubchunk2Size ();
    setSubchunk2Size (newChunkSize);
    auto oldDataLength = m_dataLength;
    m_dataLength = newDataLength;

    // Write the new data then reset file
    writeData ();
    m_Data = old_data;
    m_dataLength = oldDataLength;
    setSubchunk2Size (oldSubChunkSize);
    changeSampleRate (oldSampleRate);
    delete[] newData;
}

template<typename T>
void Wave<T>::readHeader ()
{
    checkFileName ();
    m_fileStream.open (*m_fileName, std::ios::in | std::ios::binary);
    checkFileStream ();
    getHeader (m_fileStream);
    m_fileStream.close ();
    m_byteLength = getSubchunk2Size ();
    m_dataLength = m_byteLength / 2;
}


#endif //WAVE_IO_WAVE_H