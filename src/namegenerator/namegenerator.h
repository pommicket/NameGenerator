/*
Copyright (C) 2019 Leonardo Tenenbaum

This file is part of NameGenerator.

NameGenerator is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

NameGenerator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with NameGenerator.  If not, see <https://www.gnu.org/licenses/>.

*/
#ifndef NAMEGENERATOR_NAMGENERATOR_H
#define NAMEGENERATOR_NAMGENERATOR_H

extern void  namegenerator_load(const char* trigrams_filename); /* Loads trigrams from the given file name */
extern char* namegenerator_generate_name(void); /* Generates a name with no restrictions on the length */
extern char* namegenerator_generate_name_with_length(int min_len, int max_len); /* Generates a name with length >=min_len and <max_len */

#endif /* NAMEGENERATOR_NAMGENERATOR_H */