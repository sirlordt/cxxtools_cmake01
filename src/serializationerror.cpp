/*
 * Copyright (C) 2005-2008 by Dr. Marc Boris Duerner
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * As a special exception, you may use this file as part of a free
 * software library without restriction. Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU General Public
 * License. This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Library
 * General Public License.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <cxxtools/serializationerror.h>
#include <cxxtools/serializationinfo.h>
#include <cxxtools/convert.h>
#include <sstream>

namespace cxxtools
{

SerializationError::SerializationError(const std::string& msg)
: std::runtime_error(msg)
{ }

void SerializationError::doThrow(const std::string& msg)
{
    throw SerializationError(msg);
}

static void addNodeInfo(std::string& message, const SerializationInfo& si)
{
    if (!si.name().empty())
    {
        message += " in node \"";
        message += si.name();
        message += '"';
    }

    if (!si.typeName().empty())
    {
        message += " of type \"";
        message += si.typeName();
        message += '"';
    }
}

static std::string buildMemberNotFoundMessage(const SerializationInfo& si, const std::string& member)
{
    std::string message;
    message = "Member \"";
    message += member;
    message += "\" not found";

    addNodeInfo(message, si);

    return message;
}

static std::string buildMemberNotFoundMessage(const SerializationInfo& si, unsigned idx)
{
    std::ostringstream msg;
    msg << "requested member index " << idx << " exceeds number of members " << si.memberCount();
    std::string message = msg.str();

    addNodeInfo(message, si);

    return msg.str();
}

static std::string buildConversionErrorMessage(const SerializationInfo& si, const std::string& typefrom, const std::string& typeto, const std::string& valuefrom)
{
    std::string message = "conversion from type ";
    message += typefrom;

    if (!valuefrom.empty())
    {
        message += " (\"";
        message += valuefrom;
        message += "\")";
    }

    message += " to type ";
    message += typeto;
    message += " failed";

    addNodeInfo(message, si);

    return message;
}

SerializationMemberNotFound::SerializationMemberNotFound(const std::string& member)
    : SerializationError("Missing info for '" + member + "'"),
      _member(member)
{
}

SerializationMemberNotFound::SerializationMemberNotFound(const SerializationInfo& si, const std::string& member)
    : SerializationError(buildMemberNotFoundMessage(si, member)),
      _member(member)
{
}

SerializationMemberNotFound::SerializationMemberNotFound(const SerializationInfo& si, unsigned idx)
    : SerializationError(buildMemberNotFoundMessage(si, idx)),
      _member(cxxtools::convert<std::string>(idx))
{
}

void SerializationConversionError::doThrow(const SerializationInfo& si, const std::string& typefrom, const std::string& typeto, const std::string& value)
{
    throw SerializationConversionError(buildConversionErrorMessage(si, typefrom, typeto, value));
}

} // namespace cxxtools
