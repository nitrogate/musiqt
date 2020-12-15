/*
 *  Copyright (C) 2009-2017 Leandro Nini
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

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "outputFactory.h"

#include "qaudioBackend.h"

oFactory* oFactory::instance()
{
    static oFactory o;
    return &o;
}

template <class backend>
void oFactory::regBackend()
{
    outputs_t temp;

    temp.name = backend::name;
    temp.factory = &backend::factory;
    _outputs.append(temp);
}

oFactory::oFactory()
{
    // Register backends

    regBackend<qaudioBackend>();
}

output* oFactory::get() const
{
    return _outputs[0].factory();
}
