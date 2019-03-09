Copyright 2016, 2017 Alexandre SZYDLOWSKI

------------------------------------------------------------------------
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------
Author: Alexandre SZYDLOWSKI
Date: 2016-2017
email: alexandre.szydlowski@gmail.com
------------------------------------------------------------------------

DESCRIPTION:

ASN1 Tool DLL. This tool provides an interface to create and use an ASN1 grammar, 
to serialize it in DER format, and deserialize it from a DER encoded buffer.
It can be linked directly in a project and recompiled, so that it allows you to use the c++ interface,
or it can be dynamically linked and used via the C interface. This way you don't need to recompile it.
