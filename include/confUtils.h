#pragma once

#include <fstream>
#include <exception>
#include <math.h>

template <class T>
struct Params{
  const size_t Ns;
  const size_t Nt;
  const size_t nDim;
  const size_t Nv;

  const size_t nGPar;
  const int confSize;

  Params(
  	const size_t Ns, 
  	const size_t Nt, 
  	const size_t nDim, 
  	const size_t nGPar):
  Ns(Ns), Nt(Nt), nDim(nDim), Nv(Ns*Ns*Ns * Nt),
  nGPar(nGPar), confSize(Nv * nDim * nGPar * sizeof(T))
  {}
};


template <class T>
class DataRWHeandler{
	T* data {nullptr};
	size_t confSize;

	std::fstream ioFile;
	
public:
	DataRWHeandler(const DataRWHeandler& other) = delete;
	DataRWHeandler& operator=(const DataRWHeandler& other) = delete;

	DataRWHeandler(size_t confSize): confSize(confSize) 
	{
		ioFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
		data = new T[confSize];
	};

	void open(const char* fileName, const bool read = true){
		
		auto flag = std::ios::binary;
		if (read)
			flag |= std::fstream::in;
		else 
			flag |= std::fstream::out;

		try{	
	    	ioFile.open(fileName, flag);
		} catch(std::exception& e){
			const std::string msg = 
			std::string("Data file \"") +
			std::string(fileName) + 
			std::string("\" can not be opened!");
			throw std::runtime_error(msg.c_str());
		}
	}

	void close(){
		ioFile.close();
	}

	T* readConf(){
		if(!ioFile.is_open())
			throw std::runtime_error("Data file must be opend before conf reading");
		
		static size_t counter = 0;
		
    try{
    	ioFile.read((char*)data, confSize);
    } catch(std::exception& e){
    	throw std::runtime_error("Can not read data");
    }

		counter++;

		return data;
	}

	T* getData(){
		return data;
	}

	void writeConf(){
		if(!ioFile.is_open())
			throw std::runtime_error("Data file must be opend before conf writing");

		static size_t counter = 0;

		try{
			ioFile.write((char*)data, confSize);
		} catch(std::exception& e){
			throw std::runtime_error("Can not write data");
		}

		counter++;
	}

	~DataRWHeandler()
	{
		delete[] data;
	}
};


template <class T>
class GField{
	T* data;
	const Params<T>& params;

public:
	GField(T* dataPtr, const Params<T>& params): 
	data(dataPtr), params(params) 
	{};

	inline const T* getFieldAt(
		const size_t t, 
		const size_t x,
		const size_t y,
		const size_t z,
		const size_t mu) const
	{

		const auto& Nx = params.Ns;
		const auto& Ny = params.Ns;
		const auto& Nz = params.Ns;
		const size_t i = 
			mu*params.nGPar + 
			x*params.nGPar*params.nDim + 
			y*params.nGPar*params.nDim*Nx + 
			z*params.nGPar*params.nDim*Nx*Ny + 
			t*params.nGPar*params.nDim*Nx*Ny*Nz;
		return &data[i];
	}

	inline T* getFieldAt(
		const size_t t, 
		const size_t x,
		const size_t y,
		const size_t z,
		const size_t mu)
	{

		const auto& Nx = params.Ns;
		const auto& Ny = params.Ns;
		const auto& Nz = params.Ns;
		const size_t i = 
			mu*params.nGPar + 
			x*params.nGPar*params.nDim + 
			y*params.nGPar*params.nDim*Nx + 
			z*params.nGPar*params.nDim*Nx*Ny + 
			t*params.nGPar*params.nDim*Nx*Ny*Nz;
		return &data[i];
	}
};