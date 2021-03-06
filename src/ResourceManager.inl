#include "stdafx.h"

template<typename Resource,typename Identifier>
ResourceManager<Resource,Identifier>::ResourceManager():directory(""){
}

template<typename Resource,typename Identifier>
void ResourceManager<Resource,Identifier>::setDirectory(const std::string& path){
	directory = path;
}

template<typename Resource,typename Identifier>
void ResourceManager<Resource,Identifier>::load(const Identifier& identifier,const std::string& filename){
	std::unique_ptr<Resource> resource(new Resource());

	if(!resource->loadFromFile(directory+filename)){
		throw std::runtime_error("Error: "+directory+filename+" cannot be loaded.");
	}

	resources_.insert(std::make_pair(identifier,std::move(resource)));
}

template<typename Resource,typename Identifier>
Resource& ResourceManager<Resource,Identifier>::get(const Identifier& identifier){
	auto resource = resources_.find(identifier);
	assert(resource != resources_.end() && "Could not get identifier from resource map!");
	return *resource->second;
}