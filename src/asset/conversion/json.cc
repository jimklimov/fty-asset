/*  =========================================================================
    asset_conversion_json - asset/conversion/json

    Copyright (C) 2016 - 2020 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#include "include/asset/conversion/json.h"
#include "include/fty_asset_dto.h"
#include <cxxtools/jsondeserializer.h>
#include <cxxtools/jsonserializer.h>
#include <sstream>

namespace fty { namespace conversion {

    static constexpr const char* SI_STATUS       = "status";
    static constexpr const char* SI_TYPE         = "type";
    static constexpr const char* SI_SUB_TYPE     = "sub_type";
    static constexpr const char* SI_NAME         = "name";
    static constexpr const char* SI_PRIORITY     = "priority";
    static constexpr const char* SI_PARENT       = "parent";
    static constexpr const char* SI_EXT          = "ext";
    static constexpr const char* SI_LINKED       = "linked";
    static constexpr const char* SI_PARENTS_LIST = "parents_list";

    void operator<<=(cxxtools::SerializationInfo& si, const Asset& asset)
    {
        // basic
        si.addMember(SI_STATUS) <<= int(asset.getAssetStatus());
        si.addMember(SI_TYPE) <<= asset.getAssetType();
        si.addMember(SI_SUB_TYPE) <<= asset.getAssetSubtype();
        si.addMember(SI_NAME) <<= asset.getInternalName();
        si.addMember(SI_PRIORITY) <<= asset.getPriority();
        si.addMember(SI_PARENT) <<= asset.getParentIname();
        si.addMember(SI_LINKED) <<= asset.getLinkedAssets();
        // ext map
        cxxtools::SerializationInfo& ext = si.addMember("");

        cxxtools::SerializationInfo data;
        for (const auto& e : asset.getExt()) {
            cxxtools::SerializationInfo& entry = data.addMember(e.first);
            entry <<= e.second.first;
        }
        data.setCategory(cxxtools::SerializationInfo::Category::Object);
        ext = data;
        ext.setName(SI_EXT);

        if(asset.m_parentsList.has_value()) {
            // parents list
            cxxtools::SerializationInfo data;

            [[maybe_unused]] std::vector<Asset> v = asset.m_parentsList.value();
            for (const Asset& a : v) {
                cxxtools::SerializationInfo& entry = data.addMember("");
                entry <<= a;
            }
            data.setCategory(cxxtools::SerializationInfo::Category::Object);

            cxxtools::SerializationInfo& parents = si.addMember("");
            parents                              = data;
            parents.setName(SI_PARENTS_LIST);
            parents.setCategory(cxxtools::SerializationInfo::Category::Array);
        }
    }

    void operator>>=(const cxxtools::SerializationInfo& si, fty::Asset& asset)
    {
        int         tmpInt;
        std::string tmpString;

        // status
        si.getMember(SI_STATUS) >>= tmpInt;
        asset.setAssetStatus(AssetStatus(tmpInt));

        // type
        si.getMember(SI_TYPE) >>= tmpString;
        asset.setAssetType(tmpString);

        // subtype
        si.getMember(SI_SUB_TYPE) >>= tmpString;
        asset.setAssetSubtype(tmpString);

        // internal name
        si.getMember(SI_NAME) >>= tmpString;
        asset.setInternalName(tmpString);

        // priority
        si.getMember(SI_PRIORITY) >>= tmpInt;
        asset.setPriority(tmpInt);

        // parend id
        si.getMember(SI_PARENT) >>= tmpString;
        asset.setParentIname(tmpString);

        // linked assets
        std::vector<AssetLink> tmpVector;
        si.getMember(SI_LINKED) >>= tmpVector;
        asset.setLinkedAssets(tmpVector);

        // ext map
        const cxxtools::SerializationInfo ext = si.getMember(SI_EXT);
        for (const auto& si : ext) {
            std::string key = si.name();
            std::string val;
            si >>= val;
            asset.setExtEntry(key, val);
        }

        if (si.findMember(SI_PARENTS_LIST) != NULL) {
            std::vector<fty::Asset> parentsList;
            const cxxtools::SerializationInfo parents = si.getMember(SI_PARENTS_LIST);
            for (const auto& si : parents) {
                fty::Asset a;
                si >>= a;
                parentsList.push_back(a);
            }

            asset.m_parentsList = parentsList;
        }
    }

    std::string toJson(const Asset& asset)
    {
        std::ostringstream output;

        cxxtools::SerializationInfo si;
        cxxtools::JsonSerializer    serializer(output);

        si <<= asset;
        serializer.serialize(si);

        std::string json = output.str();

        return json;
    }

    void fromJson(const std::string& json, fty::Asset& asset)
    {
        std::istringstream input(json);

        cxxtools::SerializationInfo si;
        cxxtools::JsonDeserializer  deserializer(input);

        deserializer.deserialize(si);

        si >>= asset;
    }

}} // namespace fty::conversion
