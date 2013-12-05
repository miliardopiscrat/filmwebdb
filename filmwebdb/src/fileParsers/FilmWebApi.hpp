/*
 * FilmWebApi.hpp
 *
 *  Created on: 13-10-2013
 *      Author: miliardopiscrat
 */

#ifndef FILMWEBAPI_HPP_
#define FILMWEBAPI_HPP_

#include "FilmWebApiHandle.hpp"

#include "FilmWebInfoParser.hpp"
#include "FilmWebDescrParser.hpp"
#include "FilmWebActorsParser.hpp"
#include "FilmWebDirectorParser.hpp"
#include "FilmWebImagesParser.hpp"

typedef  FilmWebApiHandle<FilmWebDescrParser>  FilmWebDescrHandle;
typedef  FilmWebApiHandle<FilmWebInfoParser>  FilmWebInfoHandle;
typedef  FilmWebApiHandle<FilmWebActorsParser>  FilmWebActorHandle;
typedef  FilmWebApiHandle<FilmWebDirectorParser>  FilmWebDirectorHandle;

typedef FilmWebApiHandle<FilmWebImagesParser>  FilmWebImagesHandle;

#endif /* FILMWEBAPI_HPP_ */
