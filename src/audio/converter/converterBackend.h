/*
 *  Copyright (C) 2009-2020 Leandro Nini
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

#ifndef CONVERTERPLUGIN_H
#define CONVERTERPLUGIN_H

#include "converter.h"

class resamplerBackend : public converter
{
protected:
    unsigned int _rate;

    unsigned int _data;

private:
    resamplerBackend();
    resamplerBackend(const resamplerBackend&);
    resamplerBackend& operator=(const resamplerBackend&);

protected:
    resamplerBackend(unsigned int srIn, unsigned int srOut, size_t size,
        unsigned int channels, unsigned int inputPrecision, unsigned int outputPrecision);

public:
    virtual ~resamplerBackend();

    /// Get pointer to buffer
    char* buffer() const override { return _buffer+_data; }

    /// Get buffer size
    size_t bufSize(int size) const override { return (size*frameRatio)-_data; }
};

/******************************************************************************/

class converterBackend : public converter
{
private:
    converterBackend();
    converterBackend(const converterBackend&);
    converterBackend& operator=(const converterBackend&);

protected:
    converterBackend(size_t size, unsigned int channels, unsigned int inputPrecision, unsigned int outputPrecision);

public:
    virtual ~converterBackend();

    /// Get pointer to buffer
    char* buffer() const override { return _buffer; }

    /// Get buffer size
    size_t bufSize(int size) const override { return size*frameRatio; }
};

#endif
