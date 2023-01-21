#!/py

import json

project_version_json_path = "version.json"
vcpkg_version_json_path = "vcpkg.json"

def GetJsonFromFile(path, flags = None):
    file = 0
    if(flags == None):
        file = open(path)
    else:
        file = open(path, flags)
        
    ret = json.load(file)
    file.close()
    return ret

def SaveJsonToFile(path, json_dict):
    json_obj = json.dumps(json_dict, indent = 4)
    file = open(path, 'w+')
    file.write(json_obj)
    file.close()
    
def SyncVersion(project_version_json, vcpkg_json):
    if "VERSION_MAJOR" not in project_version_json: raise Exception("Project's version.json is missing VERSION_MAJOR")
    if "VERSION_MINOR" not in project_version_json: raise Exception("Project's version.json is missing VERSION_MINOR")
    if "VERSION_BUILD" not in project_version_json: raise Exception("Project's version.json is missing VERSION_BUILD")
    if "version" not in vcpkg_json: raise Exception("vcpkg.json is missing version field!")

    # Order isn't guaranteed so no dict shortcuts
    v_major = project_version_json["VERSION_MAJOR"]
    v_minor = project_version_json["VERSION_MINOR"]
    v_build = project_version_json["VERSION_BUILD"]

    vcpkg_json["version"] = str(v_major) + '.' + str(v_minor) + '.' + str(v_build)

    SaveJsonToFile(vcpkg_version_json_path, vcpkg_json)

def main():
    try:
        project_version_json = GetJsonFromFile(project_version_json_path)
        vcpkg_json = GetJsonFromFile(vcpkg_version_json_path, "r+")
        SyncVersion(project_version_json, vcpkg_json)
    except Exception as ex:
        print(ex)
        return 1
        
    return 0

if __name__ == "__main__":
    main()
