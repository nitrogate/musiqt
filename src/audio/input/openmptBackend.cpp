/*
 *  Copyright (C) 2006-2017 Leandro Nini
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "openmptBackend.h"

#include "settings.h"
#include "utils.h"

#include <QComboBox>
#include <QDebug>
#include <QDial>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <algorithm>
#include <string>
#include <vector>

extern const unsigned char iconOpenmpt[990] =
{
    0x47,0x49,0x46,0x38,0x39,0x61,0x10,0x00,0x10,0x00,0xe7,0x88,0x00,0x03,0x02,0x02,
    0x00,0x03,0x02,0x04,0x02,0x02,0x04,0x03,0x03,0x03,0x04,0x03,0x08,0x05,0x04,0x08,
    0x05,0x05,0x01,0x07,0x07,0x09,0x06,0x06,0x03,0x08,0x08,0x07,0x07,0x07,0x05,0x08,
    0x08,0x11,0x05,0x05,0x08,0x08,0x07,0x09,0x08,0x08,0x0a,0x0a,0x09,0x0b,0x0a,0x0a,
    0x0d,0x0a,0x0a,0x0c,0x0b,0x0b,0x23,0x06,0x02,0x0e,0x0e,0x0d,0x26,0x08,0x04,0x27,
    0x08,0x05,0x15,0x0d,0x0c,0x2b,0x0b,0x05,0x2c,0x0b,0x06,0x19,0x10,0x0e,0x14,0x13,
    0x13,0x1d,0x11,0x0f,0x22,0x10,0x0c,0x1e,0x11,0x0e,0x14,0x14,0x14,0x32,0x0d,0x07,
    0x20,0x12,0x11,0x18,0x17,0x16,0x19,0x18,0x17,0x39,0x10,0x0a,0x3a,0x10,0x08,0x28,
    0x16,0x12,0x29,0x16,0x14,0x1b,0x1a,0x19,0x2a,0x17,0x14,0x1d,0x1c,0x1c,0x2b,0x1a,
    0x17,0x39,0x17,0x11,0x31,0x1b,0x18,0x20,0x20,0x1f,0x1d,0x21,0x21,0x46,0x17,0x0f,
    0x33,0x1c,0x17,0x22,0x21,0x20,0x54,0x15,0x0b,0x23,0x22,0x21,0x5e,0x14,0x0a,0x23,
    0x25,0x24,0x50,0x1a,0x10,0x58,0x18,0x0e,0x26,0x26,0x24,0x5e,0x19,0x0c,0x53,0x1d,
    0x15,0x5c,0x1b,0x0f,0x3d,0x24,0x21,0x78,0x15,0x0b,0x60,0x1e,0x11,0x2c,0x2b,0x2a,
    0x67,0x1d,0x0f,0x63,0x1e,0x12,0x2c,0x2c,0x2a,0x64,0x1e,0x10,0x2e,0x2d,0x2c,0x49,
    0x27,0x20,0x67,0x21,0x15,0x5b,0x26,0x1f,0x63,0x24,0x1d,0x58,0x27,0x21,0x4d,0x2c,
    0x26,0x5a,0x2a,0x23,0x72,0x24,0x18,0x9d,0x19,0x09,0x5c,0x2a,0x24,0x7a,0x23,0x18,
    0x7e,0x23,0x14,0x46,0x32,0x2e,0x37,0x37,0x35,0x82,0x27,0x15,0x7f,0x28,0x18,0x3d,
    0x39,0x37,0x67,0x2f,0x27,0x6b,0x2f,0x28,0x6b,0x30,0x29,0x7d,0x2c,0x1e,0x80,0x2c,
    0x1d,0x71,0x35,0x2c,0x54,0x3e,0x36,0x65,0x3b,0x31,0x8a,0x36,0x27,0x49,0x48,0x47,
    0x78,0x3e,0x32,0x99,0x38,0x2b,0x99,0x38,0x2c,0xb4,0x32,0x20,0x82,0x41,0x35,0x91,
    0x3e,0x30,0x82,0x44,0x37,0x86,0x43,0x36,0xc0,0x35,0x23,0x91,0x43,0x36,0x9f,0x45,
    0x39,0xba,0x3f,0x31,0xb7,0x40,0x30,0x5a,0x58,0x57,0xb3,0x43,0x35,0xb6,0x43,0x35,
    0xaf,0x46,0x37,0x9a,0x4d,0x3e,0x6d,0x5b,0x58,0x78,0x5b,0x56,0x61,0x61,0x5f,0x63,
    0x62,0x61,0xbc,0x4d,0x3d,0xa0,0x56,0x45,0xc0,0x4e,0x3f,0xbb,0x52,0x42,0xcc,0x50,
    0x40,0x8b,0x61,0x58,0xcc,0x52,0x42,0xe3,0x4f,0x3e,0x73,0x71,0x6f,0x73,0x71,0x70,
    0xec,0x54,0x42,0xdf,0x58,0x46,0xce,0x62,0x50,0x7e,0x7d,0x7a,0x7e,0x7d,0x7b,0x83,
    0x82,0x7f,0x8a,0x8a,0x88,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x21,0xf9,0x04,
    0x01,0x0a,0x00,0xff,0x00,0x2c,0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x08,
    0xbb,0x00,0xff,0xad,0xf8,0x47,0xb0,0xa0,0xc1,0x83,0x29,0x0e,0x2a,0x34,0xe8,0xa1,
    0xcb,0xc2,0x85,0x1d,0xbc,0x3c,0x54,0x88,0x01,0xc7,0xc4,0x83,0x20,0x7e,0x10,0x14,
    0x40,0x40,0x81,0x83,0x04,0x1a,0x16,0x18,0x30,0x98,0x41,0xc7,0x04,0x01,0x15,0x6a,
    0xcc,0xb8,0x01,0xe3,0x08,0x0b,0x04,0x3c,0x48,0x10,0xb4,0xf0,0xa5,0x49,0x80,0x1d,
    0x69,0xb6,0x54,0x11,0x12,0x25,0x08,0x00,0x2a,0x44,0x4a,0xfc,0x1b,0xd3,0x87,0xcd,
    0x01,0x2c,0x7e,0x9e,0xc4,0x41,0x22,0x46,0x0b,0x03,0x32,0x4e,0x7c,0x24,0xc9,0xb3,
    0x07,0xce,0x85,0x2c,0x81,0x94,0xdc,0xb9,0xf2,0xc6,0x4c,0x08,0x41,0x6d,0xa0,0x30,
    0xd1,0x23,0x47,0x0d,0x87,0x25,0x6b,0x7a,0xf0,0x91,0x42,0x67,0xce,0x89,0x41,0x67,
    0x08,0x72,0xc1,0x83,0xc6,0x84,0x0d,0x2b,0x40,0x08,0xfd,0x39,0x54,0xa7,0x45,0x19,
    0x83,0x46,0xc2,0xc4,0x78,0x31,0x65,0x48,0x21,0x40,0x76,0x68,0x50,0x58,0x18,0x41,
    0x85,0x8c,0x1c,0x86,0xc0,0x8c,0x40,0xf1,0x60,0x21,0x84,0x0d,0x22,0x5c,0xb8,0x29,
    0xf2,0xa1,0xc1,0xc4,0x01,0x0e,0x1a,0x14,0x90,0xa0,0x30,0x20,0x00,0x3b
};

#ifdef HAVE_LIBZ
#  include "libs/unzip/unzip.h"
#  ifdef _WIN32
#    include "libs/unzip/iowin32.h"
#  endif
#  define EXTZ "xmz|itz|mdz|s3z"
#endif

#define CREDITS "libopenmpt"
#define LINK    "http://lib.openmpt.org/"

const char openmptBackend::name[] = "Openmpt";

openmptConfig_t openmptBackend::_settings;

QStringList openmptBackend::_ext;

/*****************************************************************/

size_t openmptBackend::fillBuffer(void* buffer, const size_t bufferSize, const unsigned int seconds)
{
    size_t bufSize = (bufferSize/sizeof(float))/_settings.channels;
    return _settings.channels == 2
        ? _module->read_interleaved_stereo(_settings.samplerate, bufSize, (float*)buffer)
        : _module->read(_settings.samplerate, bufSize, (float*)buffer);
}

/*****************************************************************/

bool openmptBackend::init()
{
    std::vector<std::string> ext = openmpt::get_supported_extensions();
    for(std::vector<std::string>::iterator it=ext.begin(); it!=ext.end(); ++it)
    {
        _ext << (*it).c_str();
    }

    //_ext.append(",(mod).*");

#ifdef HAVE_LIBZ
    _ext << QString(EXTZ).split("|");
#endif
    return true;
}

bool openmptBackend::supports(const QString& fileName)
{
    QString ext = _ext.join("|");
    ext.prepend(".*\\.(").append(")");
    qDebug() << "sndBackend::supports: " << ext;

    QRegExp rx(ext);
    return rx.exactMatch(fileName);
}

openmptBackend::openmptBackend() :
    inputBackend(name, iconOpenmpt, 990),
    _module(nullptr)
{
    loadSettings();
}

openmptBackend::~openmptBackend()
{
    close();
}

void openmptBackend::loadSettings()
{
    _settings.samplerate = load("Frequency", 44100);
    _settings.channels = load("Channels", 2);
    _settings.resamplingMode = load("Resampling", 8);
    _settings.masterGain = load("Master gain", 0);
    _settings.stereoSeparation = load("Stereo separation", 40);
    _settings.volumeRamping = load("Volume ramping", 0);
}

void openmptBackend::saveSettings()
{
    save("Frequency", _settings.samplerate);
    save("Channels", _settings.channels);
    save("Resampling", _settings.resamplingMode);
    save("Master gain", _settings.masterGain);
    save("Stereo separation", _settings.stereoSeparation);
    save("Volume ramping", _settings.volumeRamping);
}

bool openmptBackend::open(const QString& fileName)
{
    close();

    bool tmpFile = false;
    QString fName;

#ifdef HAVE_LIBZ
    QString ext(EXTZ);
    ext.prepend(".*\\.(").append(")");
    QRegExp rx(ext);
    if (rx.exactMatch(fileName))
    {
#  ifdef _WIN32
        zlib_filefunc64_def ffunc;
        fill_win32_filefunc64(&ffunc);
#    ifdef UNICODE
        const wchar_t* tmpFileName = convertUtf(fileName);
        unzFile modZip = unzOpen2_64(tmpFileName, &ffunc);
        delete [] tmpFileName;
#    else
        unzFile modZip = unzOpen2_64(fileName.toUtf8().constData(), &ffunc);
#    endif // UNICODE
#  else
        unzFile modZip = unzOpen64(fileName.toUtf8().constData());
#  endif // _WIN32
        if (unzGoToFirstFile(modZip) != UNZ_OK)
        {
            unzClose(modZip);
            return false;
        }

        fName = tempFile(fileName);
        qDebug() << "temp file: " << fName;
        QFile modFile(fName);
        modFile.open(QIODevice::WriteOnly);
        unzOpenCurrentFile(modZip);
        int n;
        char buffer[4096];
        do {
            n = unzReadCurrentFile(modZip, buffer, 4096);
        } while (modFile.write(buffer, n));
        unzCloseCurrentFile(modZip);
        unzClose(modZip);
        tmpFile = true;
    }
#endif // HAVE_LIBZ

    if (!tmpFile)
        fName = fileName;

    QFile f(fName);
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.read(f.size());
    f.close();

    try
    {
        _module = new openmpt::module(data.constData(), data.length());
    }
    catch (const openmpt::exception &e)
    {
        utils::delPtr(_module);
        return false;
    }

    delTempFile(tmpFile, fName);

    _module->set_render_param(openmpt::module::RENDER_INTERPOLATIONFILTER_LENGTH, _settings.resamplingMode);
    _module->set_render_param(openmpt::module::RENDER_MASTERGAIN_MILLIBEL, _settings.masterGain);
    _module->set_render_param(openmpt::module::RENDER_STEREOSEPARATION_PERCENT, _settings.stereoSeparation);
    _module->set_render_param(openmpt::module::RENDER_VOLUMERAMPING_STRENGTH, _settings.volumeRamping);

    std::vector<std::string> metadata = _module->get_metadata_keys();
    for(std::vector<std::string>::iterator it=metadata.begin(); it!=metadata.end(); ++it)
    {
        qDebug() << (*it).c_str();
        if ((*it).compare("title") == 0)
            _metaData.addInfo(metaData::TITLE, _module->get_metadata("title").c_str());
        else if ((*it).compare("artist") == 0)
            _metaData.addInfo(metaData::ARTIST, _module->get_metadata("artist").c_str());
        else if ((*it).compare("message") == 0)
            _metaData.addInfo(metaData::COMMENT, _module->get_metadata("message").c_str());
    }

    time(_module->get_duration_seconds());

    songLoaded(fileName);
    return true;
}

void openmptBackend::close()
{
    if (_module != nullptr)
    {
        utils::delPtr(_module);
    }

    songLoaded(QString::null);
}

bool openmptBackend::rewind()
{
    if (_module != nullptr)
    {
        _module->set_position_order_row(0, 0);
        return true;
    }
    return false;
}

/*****************************************************************/

#define MPTSETTINGS openmptBackend::_settings

openmptConfig::openmptConfig(QWidget* win) :
    configFrame(win, openmptBackend::name, CREDITS, LINK)
{
    int val;

    matrix()->addWidget(new QLabel(tr("Frequency"), this), 0, 0);
    QComboBox *freqBox = new QComboBox(this);
    matrix()->addWidget(freqBox, 0, 1);
    {
        QStringList items;
        items << "11025" << "22050" << "44100" << "48000";
        freqBox->addItems(items);
        freqBox->setMaxVisibleItems(items.size());
    }
    switch (MPTSETTINGS.samplerate)
    {
    case 11025:
        val = 0;
        break;
    case 22050:
        val = 1;
        break;
    default:
    case 44100:
        val = 2;
        break;
    case 48000:
        val = 3;
        break;
    }
    freqBox->setCurrentIndex(val);
    connect(freqBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCmdFrequency(int)));

    matrix()->addWidget(new QLabel(tr("Channels"), this));
    QComboBox *chanBox = new QComboBox(this);
    matrix()->addWidget(chanBox);
    {
        QStringList items;
        items << "Mono" << "Stereo";
        chanBox->addItems(items);
        chanBox->setMaxVisibleItems(items.size());
    }
    chanBox->setCurrentIndex(MPTSETTINGS.channels-1);
    connect(chanBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCmdChannels(int)));

    matrix()->addWidget(new QLabel(tr("Resampling"), this));
    QComboBox *resBox = new QComboBox(this);
    matrix()->addWidget(resBox);
    {
        QStringList items;
        items << "Zero order hold" << "Linear" << "Cubic Spline" << "Sinc 8 taps";
        resBox->addItems(items);
        resBox->setMaxVisibleItems(items.size());
    }
    switch (MPTSETTINGS.resamplingMode)
    {
    case 1:
        val = 0;
        break;
    case 2:
        val = 1;
        break;
    default:
    case 4:
        val = 2;
        break;
    case 8:
        val = 3;
        break;
    }
    resBox->setCurrentIndex(val);
    connect(resBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCmdResampling(int)));

    //
    QHBoxLayout *hf = new QHBoxLayout();
    extraBottom()->addLayout(hf);

    QDial *knob;
    QLabel *tf;

    QVBoxLayout *vert = new QVBoxLayout();
    hf->addLayout(vert);
    QGridLayout *mat = new QGridLayout();
    vert->addLayout(mat);

    mat->addWidget(new QLabel(tr("Master Gain"), this), 0, 0);
    knob = new QDial(this);
    knob->setRange(0, 100);
    //knob->setTickDelta(10);
    mat->addWidget(knob, 1, 0);
    tf = new QLabel(this);
    tf->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    tf->setAlignment(Qt::AlignCenter);
    mat->addWidget(tf, 2, 0);
    connect(knob, SIGNAL(valueChanged(int)), tf, SLOT(setNum(int)));
    connect(knob, SIGNAL(valueChanged(int)), this, SLOT(onCmdMasterGain(int)));
    knob->setValue(MPTSETTINGS.masterGain);

    mat->addWidget(new QLabel(tr("Stereo Separation"), this), 0, 1);
    knob = new QDial(this);
    knob->setRange(0, 200);
    //knob->setTickDelta(20);
    mat->addWidget(knob, 1, 1);
    tf = new QLabel(this);
    tf->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    tf->setAlignment(Qt::AlignCenter);
    mat->addWidget(tf, 2, 1);
    connect(knob, SIGNAL(valueChanged(int)), tf, SLOT(setNum(int)));
    connect(knob, SIGNAL(valueChanged(int)), this, SLOT(onCmdStereoSeparation(int)));
    knob->setValue(MPTSETTINGS.stereoSeparation);

    mat->addWidget(new QLabel(tr("Volume Ramping"), this), 0, 2);
    knob = new QDial(this);
    knob->setRange(-1, 10);
    //knob->setTickDelta(1);
    mat->addWidget(knob, 1, 2);
    tf = new QLabel(this);
    tf->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    tf->setAlignment(Qt::AlignCenter);
    mat->addWidget(tf, 2, 2);
    connect(knob, SIGNAL(valueChanged(int)), tf, SLOT(setNum(int)));
    connect(knob, SIGNAL(valueChanged(int)), this, SLOT(onCmdVolumeRamping(int)));
    knob->setValue(MPTSETTINGS.volumeRamping);
}

void openmptConfig::onCmdFrequency(int val)
{
    switch (val)
    {
    case 0:
        MPTSETTINGS.samplerate = 11025;
        break;
    case 1:
        MPTSETTINGS.samplerate = 22050;
        break;
    case 2:
        MPTSETTINGS.samplerate = 44100;
        break;
    case 3:
        MPTSETTINGS.samplerate = 48000;
        break;
    }
}

void openmptConfig::onCmdChannels(int val)
{
    MPTSETTINGS.channels = val+1;
}

void openmptConfig::onCmdResampling(int val)
{
    switch (val)
    {
    case 0:
        MPTSETTINGS.resamplingMode = 1;
        break;
    case 1:
        MPTSETTINGS.resamplingMode = 2;
        break;
    case 2:
        MPTSETTINGS.resamplingMode = 4;
        break;
    case 3:
        MPTSETTINGS.resamplingMode = 8;
        break;
    }
}

void openmptConfig::onCmdMasterGain(int val)
{
    MPTSETTINGS.masterGain = val;
}

void openmptConfig::onCmdStereoSeparation(int val)
{
    MPTSETTINGS.stereoSeparation = val;
}

void openmptConfig::onCmdVolumeRamping(int val)
{
    MPTSETTINGS.volumeRamping = val;
}
