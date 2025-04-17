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

# DESCRIPTION:

ASN1 Tool DLL. This tool provides an interface to create and use an ASN1 grammar,
to serialize it in DER format, and deserialize it from a DER encoded buffer.
It can be linked directly in a project and recompiled, so that it allows you to use the c++ interface,
or it can be dynamically linked and used via the C interface. This way you don't need to recompile it.

## GUI
Q-ASN1. This executable is to be used with the ASN1 DLL and QT Script DLL. The DLL must be recompiled together with this program.
Q-ASN1 provides a GUI interface to view and edit an ASN1 tree.
It also provides a script editor to allow the user to define an ASN1 grammar in JavaScript.
It is still able to use hardcoded grammars, base on the DLL interface, but they need to be included and compiled in the project to be used.

# DEPENDENCIES - Ubuntu 22.04
apt install qt6-base-dev qt6-base-dev-tools qt6-webengine-dev flex bison
