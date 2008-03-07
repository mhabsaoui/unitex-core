/*
  * Unitex
  *
  * Copyright (C) 2001-2008 Universit� Paris-Est Marne-la-Vall�e <unitex@univ-mlv.fr>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  * 
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
  *
  */

//  The purpose is to call locate  with one Fst from dico.exe
//  by Alexis Neme 15/11/2005
// we simulate the command line ( the argv[]) of locate.exe from a calling program.


#ifndef LocateAsRoutineH
#define LocateAsRoutineH

#include "LocateConstants.h"

int main_Locate(int, char**); 
void launch_locate_as_routine(char*,char*,char*,OutputPolicy);


#endif

