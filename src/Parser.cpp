#include "../include/Parser.hpp"

Parser::Parser()
{
    length_In = 0u;
    length_Out = 0u;
    fileArray_In = NULL;
    fileArray_Out = NULL;
    count_In = 0u;
    count_Out = 0u;
}

Parser::Parser(unsigned length_in)
{
    length_In = length_in;
    length_Out = length_in;
    fileArray_In = new std::ifstream[length_in];
    fileArray_Out = new std::ofstream[length_in];
    count_In = 0u;
    count_Out = 0u;
}

Parser::Parser(const Parser &parser_in)
{
    length_In = parser_in.length_In;
    length_Out = parser_in.length_Out;
    fileArray_In = new std::ifstream[length_In];
    fileArray_Out = new std::ofstream[length_Out];
    count_In = 0u;
    count_Out = 0u;
}

Parser &Parser::operator=(const Parser &parser_in)
{
    length_In = parser_in.length_In;
    length_Out = parser_in.length_Out;
    fileArray_In = new std::ifstream[length_In];
    fileArray_Out = new std::ofstream[length_Out];
    count_In = 0u;
    count_Out = 0u;
    return *this;
}

void Parser::ImportConfiguration(std::ifstream &file_in, std::string &name_out, unsigned &length_out, ParserType &type_out, unsigned &iteration_out)
{
    char aux[100];
    unsigned type;
    file_in.getline(aux, 100);
    name_out = aux;
    if (name_out.size() > 0u && name_out[name_out.size() - 1u] == '\r')
    {
        name_out.pop_back();
    }
    file_in >> length_out;
    file_in >> type;
    file_in >> iteration_out;
    type_out = (ParserType)type;
}

void Parser::ExportConfiguration(std::ofstream &file_in, std::string name_in, unsigned length_in, ParserType type_in, std::streampos &iterationPosition_out)
{
    std::string iteration_string = std::to_string(0u) + "    ";
    file_in << name_in << "\n";
    file_in << length_in << "\t";
    file_in << (unsigned)type_in << "\t";
    iterationPosition_out = file_in.tellp();
    file_in << iteration_string << "\n";
}

void Parser::ImportValues(std::ifstream &file_in, unsigned length_in, ParserType type_in, void *&values_out, unsigned iteration_in)
{
    std::streampos position = file_in.tellg();
    for (unsigned i = 0u; i < iteration_in * length_in; i++)
    {
        file_in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    switch (type_in)
    {
    case ParserType::Char:
        values_out = new char[length_in];
        std::fill((char *)values_out, ((char *)values_out) + length_in, 0);
        ImportValues<char>(file_in, length_in, values_out);
        break;
    case ParserType::UChar:
        values_out = new unsigned char[length_in];
        std::fill((unsigned char *)values_out, ((unsigned char *)values_out) + length_in, 0);
        ImportValues<unsigned char>(file_in, length_in, values_out);
        break;
    case ParserType::SInt:
        values_out = new short int[length_in];
        std::fill((short int *)values_out, ((short int *)values_out) + length_in, 0);
        ImportValues<short int>(file_in, length_in, values_out);
        break;
    case ParserType::SUInt:
        values_out = new short unsigned int[length_in];
        std::fill((short unsigned int *)values_out, ((short unsigned int *)values_out) + length_in, 0);
        ImportValues<short unsigned int>(file_in, length_in, values_out);
        break;
    case ParserType::Int:
        values_out = new int[length_in];
        std::fill((int *)values_out, ((int *)values_out) + length_in, 0);
        ImportValues<int>(file_in, length_in, values_out);
        break;
    case ParserType::UInt:
        values_out = new unsigned int[length_in];
        std::fill((unsigned int *)values_out, ((unsigned int *)values_out) + length_in, 0);
        ImportValues<unsigned int>(file_in, length_in, values_out);
        break;
    case ParserType::LInt:
        values_out = new long int[length_in];
        std::fill((long int *)values_out, ((long int *)values_out) + length_in, 0);
        ImportValues<long int>(file_in, length_in, values_out);
        break;
    case ParserType::LUInt:
        values_out = new long unsigned int[length_in];
        std::fill((long unsigned int *)values_out, ((long unsigned int *)values_out) + length_in, 0);
        ImportValues<long unsigned int>(file_in, length_in, values_out);
        break;
    case ParserType::LLInt:
        values_out = new long long int[length_in];
        std::fill((long long int *)values_out, ((long long int *)values_out) + length_in, 0);
        ImportValues<long long int>(file_in, length_in, values_out);
        break;
    case ParserType::LLUInt:
        values_out = new long long unsigned int[length_in];
        std::fill((long long unsigned int *)values_out, ((long long unsigned int *)values_out) + length_in, 0);
        ImportValues<long long unsigned int>(file_in, length_in, values_out);
        break;
    case ParserType::Float:
        values_out = new float[length_in];
        std::fill((float *)values_out, ((float *)values_out) + length_in, 0);
        ImportValues<float>(file_in, length_in, values_out);
        break;
    case ParserType::Double:
        values_out = new double[length_in];
        std::fill((double *)values_out, ((double *)values_out) + length_in, 0);
        ImportValues<double>(file_in, length_in, values_out);
        break;
    case ParserType::LDouble:
        values_out = new long double[length_in];
        std::fill((long double *)values_out, ((long double *)values_out) + length_in, 0);
        ImportValues<long double>(file_in, length_in, values_out);
        break;
    default:
        break;
    }
    file_in.seekg(position);
}

void Parser::ExportValues(std::ofstream &file_in, unsigned length_in, ParserType type_in, void *values_in, std::streampos &iterationPosition_in, unsigned iteration_in)
{
    std::streampos position = file_in.tellp();
    file_in.seekp(iterationPosition_in);
    file_in << iteration_in + 1u;
    file_in.seekp(position);
    switch (type_in)
    {
    case ParserType::Char:
        ExportValues<char>(file_in, length_in, values_in);
        break;
    case ParserType::UChar:
        ExportValues<unsigned char>(file_in, length_in, values_in);
        break;
    case ParserType::SInt:
        ExportValues<short int>(file_in, length_in, values_in);
        break;
    case ParserType::SUInt:
        ExportValues<short unsigned int>(file_in, length_in, values_in);
        break;
    case ParserType::Int:
        ExportValues<int>(file_in, length_in, values_in);
        break;
    case ParserType::UInt:
        ExportValues<unsigned int>(file_in, length_in, values_in);
        break;
    case ParserType::LInt:
        ExportValues<long int>(file_in, length_in, values_in);
        break;
    case ParserType::LUInt:
        ExportValues<long unsigned int>(file_in, length_in, values_in);
        break;
    case ParserType::LLInt:
        ExportValues<long long int>(file_in, length_in, values_in);
        break;
    case ParserType::LLUInt:
        ExportValues<long long unsigned int>(file_in, length_in, values_in);
        break;
    case ParserType::Float:
        ExportValues<float>(file_in, length_in, values_in);
        break;
    case ParserType::Double:
        ExportValues<double>(file_in, length_in, values_in);
        break;
    case ParserType::LDouble:
        ExportValues<long double>(file_in, length_in, values_in);
        break;
    default:
        break;
    }
}

void Parser::ImportAllValues(std::ifstream &file_in, unsigned length_in, ParserType type_in, void *&values_out, unsigned iteration_in)
{
    unsigned size = length_in * iteration_in;
    switch (type_in)
    {
    case ParserType::Char:
        values_out = new char[size];
        std::fill((char *)values_out, ((char *)values_out) + size, 0);
        ImportValues<char>(file_in, size, values_out);
        break;
    case ParserType::UChar:
        values_out = new unsigned char[size];
        std::fill((unsigned char *)values_out, ((unsigned char *)values_out) + size, 0);
        ImportValues<unsigned char>(file_in, size, values_out);
        break;
    case ParserType::SInt:
        values_out = new short int[size];
        std::fill((short int *)values_out, ((short int *)values_out) + size, 0);
        ImportValues<short int>(file_in, size, values_out);
        break;
    case ParserType::SUInt:
        values_out = new short unsigned int[size];
        std::fill((short unsigned int *)values_out, ((short unsigned int *)values_out) + size, 0);
        ImportValues<short unsigned int>(file_in, size, values_out);
        break;
    case ParserType::Int:
        values_out = new int[size];
        std::fill((int *)values_out, ((int *)values_out) + size, 0);
        ImportValues<int>(file_in, size, values_out);
        break;
    case ParserType::UInt:
        values_out = new unsigned int[size];
        std::fill((unsigned int *)values_out, ((unsigned int *)values_out) + size, 0);
        ImportValues<unsigned int>(file_in, size, values_out);
        break;
    case ParserType::LInt:
        values_out = new long int[size];
        std::fill((long int *)values_out, ((long int *)values_out) + size, 0);
        ImportValues<long int>(file_in, size, values_out);
        break;
    case ParserType::LUInt:
        values_out = new long unsigned int[size];
        std::fill((long unsigned int *)values_out, ((long unsigned int *)values_out) + size, 0);
        ImportValues<long unsigned int>(file_in, size, values_out);
        break;
    case ParserType::LLInt:
        values_out = new long long int[size];
        std::fill((long long int *)values_out, ((long long int *)values_out) + size, 0);
        ImportValues<long long int>(file_in, size, values_out);
        break;
    case ParserType::LLUInt:
        values_out = new long long unsigned int[size];
        std::fill((long long unsigned int *)values_out, ((long long unsigned int *)values_out) + size, 0);
        ImportValues<long long unsigned int>(file_in, size, values_out);
        break;
    case ParserType::Float:
        values_out = new float[size];
        std::fill((float *)values_out, ((float *)values_out) + size, 0);
        ImportValues<float>(file_in, size, values_out);
        break;
    case ParserType::Double:
        values_out = new double[size];
        std::fill((double *)values_out, ((double *)values_out) + size, 0);
        ImportValues<double>(file_in, size, values_out);
        break;
    case ParserType::LDouble:
        values_out = new long double[size];
        std::fill((long double *)values_out, ((long double *)values_out) + size, 0);
        ImportValues<long double>(file_in, size, values_out);
        break;
    default:
        break;
    }
}

void Parser::ExportAllValues(std::ofstream &file_in, unsigned length_in, ParserType type_in, void *values_in, std::streampos &iterationPosition_in, unsigned iteration_in)
{
    std::streampos position = file_in.tellp();
    file_in.seekp(iterationPosition_in);
    file_in << iteration_in;
    file_in.seekp(position);
    unsigned size = length_in * iteration_in;
    switch (type_in)
    {
    case ParserType::Char:
        ExportValues<char>(file_in, size, values_in);
        break;
    case ParserType::UChar:
        ExportValues<unsigned char>(file_in, size, values_in);
        break;
    case ParserType::SInt:
        ExportValues<short int>(file_in, size, values_in);
        break;
    case ParserType::SUInt:
        ExportValues<short unsigned int>(file_in, size, values_in);
        break;
    case ParserType::Int:
        ExportValues<int>(file_in, size, values_in);
        break;
    case ParserType::UInt:
        ExportValues<unsigned int>(file_in, size, values_in);
        break;
    case ParserType::LInt:
        ExportValues<long int>(file_in, size, values_in);
        break;
    case ParserType::LUInt:
        ExportValues<long unsigned int>(file_in, size, values_in);
        break;
    case ParserType::LLInt:
        ExportValues<long long int>(file_in, size, values_in);
        break;
    case ParserType::LLUInt:
        ExportValues<long long unsigned int>(file_in, size, values_in);
        break;
    case ParserType::Float:
        ExportValues<float>(file_in, size, values_in);
        break;
    case ParserType::Double:
        ExportValues<double>(file_in, size, values_in);
        break;
    case ParserType::LDouble:
        ExportValues<long double>(file_in, size, values_in);
        break;
    default:
        break;
    }
}

void Parser::ImportConfigurationBinary(std::ifstream &file_in, std::string &name_out, unsigned &length_out, ParserType &type_out, unsigned &iteration_out)
{
    unsigned type = 0u;
    unsigned size = 0u;
    file_in.read((char *)(&size), sizeof(unsigned));
    char *aux = new (std::nothrow) char[size];
    file_in.read(aux, sizeof(char) * size);
    file_in.read((char *)(&length_out), sizeof(unsigned));
    file_in.read((char *)(&(type)), sizeof(unsigned));
    file_in.read((char *)(&(iteration_out)), sizeof(unsigned));
    name_out = std::string(aux, size);
    type_out = (ParserType)type;
    delete[] aux;
}

void Parser::ExportConfigurationBinary(std::ofstream &file_in, std::string name_in, unsigned length_in, ParserType type_in, std::streampos &iterationPosition_out)
{
    unsigned size = name_in.size();
    unsigned type = (unsigned)type_in;
    unsigned iteration = 0u;
    file_in.write((char *)(&size), sizeof(unsigned));
    file_in.write(name_in.c_str(), sizeof(char) * size);
    file_in.write((char *)(&length_in), sizeof(unsigned));
    file_in.write((char *)(&(type)), sizeof(unsigned));
    iterationPosition_out = file_in.tellp();
    file_in.write((char *)(&iteration), sizeof(unsigned));
}

void Parser::ImportValuesBinary(std::ifstream &file_in, unsigned length_in, ParserType type_in, void *&values_out, unsigned iteration_in)
{
    std::streampos position = file_in.tellg();
    file_in.seekg(position + (std::streamoff)(length_in * iteration_in));
    switch (type_in)
    {
    case ParserType::Char:
        values_out = new char[length_in];
        std::fill((char *)values_out, ((char *)values_out) + length_in, 0);
        ImportValuesBinary<char>(file_in, length_in, values_out);
        break;
    case ParserType::UChar:
        values_out = new unsigned char[length_in];
        std::fill((unsigned char *)values_out, ((unsigned char *)values_out) + length_in, 0);
        ImportValuesBinary<unsigned char>(file_in, length_in, values_out);
        break;
    case ParserType::SInt:
        values_out = new short int[length_in];
        std::fill((short int *)values_out, ((short int *)values_out) + length_in, 0);
        ImportValuesBinary<short int>(file_in, length_in, values_out);
        break;
    case ParserType::SUInt:
        values_out = new short unsigned int[length_in];
        std::fill((short unsigned int *)values_out, ((short unsigned int *)values_out) + length_in, 0);
        ImportValuesBinary<short unsigned int>(file_in, length_in, values_out);
        break;
    case ParserType::Int:
        values_out = new int[length_in];
        std::fill((int *)values_out, ((int *)values_out) + length_in, 0);
        ImportValuesBinary<int>(file_in, length_in, values_out);
        break;
    case ParserType::UInt:
        values_out = new unsigned int[length_in];
        std::fill((unsigned int *)values_out, ((unsigned int *)values_out) + length_in, 0);
        ImportValuesBinary<unsigned int>(file_in, length_in, values_out);
        break;
    case ParserType::LInt:
        values_out = new long int[length_in];
        std::fill((long int *)values_out, ((long int *)values_out) + length_in, 0);
        ImportValuesBinary<long int>(file_in, length_in, values_out);
        break;
    case ParserType::LUInt:
        values_out = new long unsigned int[length_in];
        std::fill((long unsigned int *)values_out, ((long unsigned int *)values_out) + length_in, 0);
        ImportValuesBinary<long unsigned int>(file_in, length_in, values_out);
        break;
    case ParserType::LLInt:
        values_out = new long long int[length_in];
        std::fill((long long int *)values_out, ((long long int *)values_out) + length_in, 0);
        ImportValuesBinary<long long int>(file_in, length_in, values_out);
        break;
    case ParserType::LLUInt:
        values_out = new long long unsigned int[length_in];
        std::fill((long long unsigned int *)values_out, ((long long unsigned int *)values_out) + length_in, 0);
        ImportValuesBinary<long long unsigned int>(file_in, length_in, values_out);
        break;
    case ParserType::Float:
        values_out = new float[length_in];
        std::fill((float *)values_out, ((float *)values_out) + length_in, 0);
        ImportValuesBinary<float>(file_in, length_in, values_out);
        break;
    case ParserType::Double:
        values_out = new double[length_in];
        std::fill((double *)values_out, ((double *)values_out) + length_in, 0);
        ImportValuesBinary<double>(file_in, length_in, values_out);
        break;
    case ParserType::LDouble:
        values_out = new long double[length_in];
        std::fill((long double *)values_out, ((long double *)values_out) + length_in, 0);
        ImportValuesBinary<long double>(file_in, length_in, values_out);
        break;
    default:
        break;
    }
    file_in.seekg(position);
}

void Parser::ExportValuesBinary(std::ofstream &file_in, unsigned length_in, ParserType type_in, void *values_in, std::streampos &iterationPosition_in, unsigned iteration_in)
{
    std::streampos position = file_in.tellp();
    file_in.seekp(iterationPosition_in);
    unsigned it = iteration_in + 1u;
    file_in.write((char *)(&it), sizeof(unsigned));
    file_in.seekp(position);
    switch (type_in)
    {
    case ParserType::Char:
        ExportValuesBinary<char>(file_in, length_in, values_in);
        break;
    case ParserType::UChar:
        ExportValuesBinary<unsigned char>(file_in, length_in, values_in);
        break;
    case ParserType::SInt:
        ExportValuesBinary<short int>(file_in, length_in, values_in);
        break;
    case ParserType::SUInt:
        ExportValuesBinary<short unsigned int>(file_in, length_in, values_in);
        break;
    case ParserType::Int:
        ExportValuesBinary<int>(file_in, length_in, values_in);
        break;
    case ParserType::UInt:
        ExportValuesBinary<unsigned int>(file_in, length_in, values_in);
        break;
    case ParserType::LInt:
        ExportValuesBinary<long int>(file_in, length_in, values_in);
        break;
    case ParserType::LUInt:
        ExportValuesBinary<long unsigned int>(file_in, length_in, values_in);
        break;
    case ParserType::LLInt:
        ExportValuesBinary<long long int>(file_in, length_in, values_in);
        break;
    case ParserType::LLUInt:
        ExportValuesBinary<long long unsigned int>(file_in, length_in, values_in);
        break;
    case ParserType::Float:
        ExportValuesBinary<float>(file_in, length_in, values_in);
        break;
    case ParserType::Double:
        ExportValuesBinary<double>(file_in, length_in, values_in);
        break;
    case ParserType::LDouble:
        ExportValuesBinary<long double>(file_in, length_in, values_in);
        break;
    default:
        break;
    }
}

void Parser::ImportAllValuesBinary(std::ifstream &file_in, unsigned length_in, ParserType type_in, void *&values_out, unsigned iteration_in)
{
    unsigned size = length_in * iteration_in;
    switch (type_in)
    {
    case ParserType::Char:
        values_out = new char[size];
        std::fill((char *)values_out, ((char *)values_out) + size, 0);
        ImportValuesBinary<char>(file_in, size, values_out);
        break;
    case ParserType::UChar:
        values_out = new unsigned char[size];
        std::fill((unsigned char *)values_out, ((unsigned char *)values_out) + size, 0);
        ImportValuesBinary<unsigned char>(file_in, size, values_out);
        break;
    case ParserType::SInt:
        values_out = new short int[size];
        std::fill((short int *)values_out, ((short int *)values_out) + size, 0);
        ImportValuesBinary<short int>(file_in, size, values_out);
        break;
    case ParserType::SUInt:
        values_out = new short unsigned int[size];
        std::fill((short unsigned int *)values_out, ((short unsigned int *)values_out) + size, 0);
        ImportValuesBinary<short unsigned int>(file_in, size, values_out);
        break;
    case ParserType::Int:
        values_out = new int[size];
        std::fill((int *)values_out, ((int *)values_out) + size, 0);
        ImportValuesBinary<int>(file_in, size, values_out);
        break;
    case ParserType::UInt:
        values_out = new unsigned int[size];
        std::fill((unsigned int *)values_out, ((unsigned int *)values_out) + size, 0);
        ImportValuesBinary<unsigned int>(file_in, size, values_out);
        break;
    case ParserType::LInt:
        values_out = new long int[size];
        std::fill((long int *)values_out, ((long int *)values_out) + size, 0);
        ImportValuesBinary<long int>(file_in, size, values_out);
        break;
    case ParserType::LUInt:
        values_out = new long unsigned int[size];
        std::fill((long unsigned int *)values_out, ((long unsigned int *)values_out) + size, 0);
        ImportValuesBinary<long unsigned int>(file_in, size, values_out);
        break;
    case ParserType::LLInt:
        values_out = new long long int[size];
        std::fill((long long int *)values_out, ((long long int *)values_out) + size, 0);
        ImportValuesBinary<long long int>(file_in, size, values_out);
        break;
    case ParserType::LLUInt:
        values_out = new long long unsigned int[size];
        std::fill((long long unsigned int *)values_out, ((long long unsigned int *)values_out) + size, 0);
        ImportValuesBinary<long long unsigned int>(file_in, size, values_out);
        break;
    case ParserType::Float:
        values_out = new float[size];
        std::fill((float *)values_out, ((float *)values_out) + size, 0);
        ImportValuesBinary<float>(file_in, size, values_out);
        break;
    case ParserType::Double:
        values_out = new double[size];
        std::fill((double *)values_out, ((double *)values_out) + size, 0);
        ImportValuesBinary<double>(file_in, size, values_out);
        break;
    case ParserType::LDouble:
        values_out = new long double[size];
        std::fill((long double *)values_out, ((long double *)values_out) + size, 0);
        ImportValuesBinary<long double>(file_in, size, values_out);
        break;
    default:
        break;
    }
}

void Parser::ExportAllValuesBinary(std::ofstream &file_in, unsigned length_in, ParserType type_in, void *values_in, std::streampos &iterationPosition_in, unsigned iteration_in)
{
    std::streampos position = file_in.tellp();
    file_in.seekp(iterationPosition_in);
    file_in.write((char *)&iteration_in, sizeof(unsigned));
    file_in.seekp(position);
    unsigned size = length_in * iteration_in;
    switch (type_in)
    {
    case ParserType::Char:
        ExportValuesBinary<char>(file_in, size, values_in);
        break;
    case ParserType::UChar:
        ExportValuesBinary<unsigned char>(file_in, size, values_in);
        break;
    case ParserType::SInt:
        ExportValuesBinary<short int>(file_in, size, values_in);
        break;
    case ParserType::SUInt:
        ExportValuesBinary<short unsigned int>(file_in, size, values_in);
        break;
    case ParserType::Int:
        ExportValuesBinary<int>(file_in, size, values_in);
        break;
    case ParserType::UInt:
        ExportValuesBinary<unsigned int>(file_in, size, values_in);
        break;
    case ParserType::LInt:
        ExportValuesBinary<long int>(file_in, size, values_in);
        break;
    case ParserType::LUInt:
        ExportValuesBinary<long unsigned int>(file_in, size, values_in);
        break;
    case ParserType::LLInt:
        ExportValuesBinary<long long int>(file_in, size, values_in);
        break;
    case ParserType::LLUInt:
        ExportValuesBinary<long long unsigned int>(file_in, size, values_in);
        break;
    case ParserType::Float:
        ExportValuesBinary<float>(file_in, size, values_in);
        break;
    case ParserType::Double:
        ExportValuesBinary<double>(file_in, size, values_in);
        break;
    case ParserType::LDouble:
        ExportValuesBinary<long double>(file_in, size, values_in);
        break;
    default:
        break;
    }
}

void Parser::DeleteValues(void *values_in, ParserType type_in)
{
    switch (type_in)
    {
    case ParserType::Char:
        delete[] ((char *)values_in);
        break;
    case ParserType::UChar:
        delete[] ((unsigned char *)values_in);
        break;
    case ParserType::SInt:
        delete[] ((short int *)values_in);
        break;
    case ParserType::SUInt:
        delete[] ((short unsigned int *)values_in);
        break;
    case ParserType::Int:
        delete[] ((int *)values_in);
        break;
    case ParserType::UInt:
        delete[] ((unsigned int *)values_in);
        break;
    case ParserType::LInt:
        delete[] ((long int *)values_in);
        break;
    case ParserType::LUInt:
        delete[] ((long unsigned int *)values_in);
        break;
    case ParserType::LLInt:
        delete[] ((long long int *)values_in);
        break;
    case ParserType::LLUInt:
        delete[] ((long long unsigned int *)values_in);
        break;
    case ParserType::Float:
        delete[] ((float *)values_in);
        break;
    case ParserType::Double:
        delete[] ((double *)values_in);
        break;
    case ParserType::LDouble:
        delete[] ((long double *)values_in);
        break;
    default:
        break;
    }
}

void Parser::ConvertToBinary(std::string path_in, std::string path_out, std::string extension_in)
{
    std::string name;
    unsigned length;
    ParserType type;
    void *values;
    std::string name_in;
    std::string name_out;
    for (const auto &entry : std::filesystem::directory_iterator(path_in))
    {
        name_in = path_in + entry.path().filename().string();
        name_out = path_out + entry.path().stem().string() + extension_in;

        std::ifstream in(name_in);
        std::ofstream out(name_out, std::ios::binary | std::ios::trunc);

        std::streampos iterationPosition;
        unsigned iteration = 0u;

        ImportConfiguration(in, name, length, type, iteration);
        ImportAllValues(in, length, type, values, iteration);

        ExportConfigurationBinary(out, name, length, type, iterationPosition);
        ExportAllValuesBinary(out, length, type, values, iterationPosition, iteration);

        DeleteValues(values, type);

        out.close();
        in.close();
    }
}

void Parser::ConvertToText(std::string path_in, std::string path_out, std::string extension_in)
{
    std::string name;
    unsigned length;
    ParserType type;
    void *values;
    std::string name_in;
    std::string name_out;
    for (const auto &entry : std::filesystem::directory_iterator(path_in))
    {
        name_in = path_in + entry.path().filename().string();
        name_out = path_out + entry.path().stem().string() + extension_in;

        std::ifstream in(name_in, std::ios::binary);
        std::ofstream out(name_out, std::ios::trunc);

        std::streampos iterationPosition;
        unsigned iteration = 0u;
        length = 0u;

        ImportConfigurationBinary(in, name, length, type, iteration);
        ImportAllValuesBinary(in, length, type, values, iteration);

        ExportConfiguration(out, name, length, type, iterationPosition);
        ExportAllValues(out, length, type, values, iterationPosition, iteration);

        DeleteValues(values, type);

        out.close();
        in.close();
    }
}

unsigned Parser::OpenFileIn(std::string path_in, std::string name_in, std::string extension_in, std::ios::openmode mode_in, unsigned index_in)
{
    std::cout << "Trying to open file with name: " << name_in << "\n";
    if (index_in == UINT_MAX_VALUE)
    {
        if (count_In >= length_In)
        {
            std::cout << "Error: Too many files are open at the moment. Use old indexes to reopen in the same place or close all files.";
            return UINT_MAX_VALUE;
        }
        fileArray_In[count_In].open(path_in + name_in + extension_in, mode_in);
        if (!fileArray_In[count_In].is_open())
        {
            std::cout << "Error: Failed to open file.\n";
        }
        count_In++;
        return count_In - 1;
    }
    else
    {
        if (index_in >= length_In)
        {
            std::cout << "Error: Index is out of range.";
            return UINT_MAX_VALUE;
        }
        if (fileArray_In[index_in].is_open())
        {
            fileArray_In[index_in].close();
        }
        fileArray_In[index_in].open(path_in + name_in + extension_in, mode_in);
        return index_in;
    }
}

unsigned Parser::OpenFileOut(std::string path_in, std::string name_in, std::string extension_in, std::ios::openmode mode_in, unsigned index_in)
{
    std::cout << "Trying to open file with name: " << name_in << "\n";
    if (index_in == UINT_MAX_VALUE)
    {
        if (count_Out >= length_Out)
        {
            std::cout << "Error: Too many files are open at the moment. Use old indexes to reopen in the same place or close all files.";
            return UINT_MAX_VALUE;
        }
        fileArray_Out[count_Out].open(path_in + name_in + extension_in, mode_in);
        if (!fileArray_Out[count_Out].is_open())
        {
            std::cout << "Error: Failed to open file.\n";
        }
        count_Out++;
        return count_Out - 1;
    }
    else
    {
        if (index_in >= length_Out)
        {
            std::cout << "Error: Index is out of range.";
            return UINT_MAX_VALUE;
        }
        if (fileArray_Out[index_in].is_open())
        {
            fileArray_Out[index_in].close();
        }
        fileArray_Out[index_in].open(path_in + name_in + extension_in, mode_in);
        return index_in;
    }
}

std::ifstream &Parser::GetStreamIn(unsigned index_in)
{
    return fileArray_In[index_in];
}
std::ofstream &Parser::GetStreamOut(unsigned index_in)
{
    return fileArray_Out[index_in];
}

void Parser::CloseFileIn(unsigned index_in)
{
    fileArray_In[index_in].close();
}
void Parser::CloseFileOut(unsigned index_in)
{
    fileArray_Out[index_in].close();
}

void Parser::CloseAllFileIn()
{
    for (unsigned i = 0u; i < length_In; i++)
    {
        if (fileArray_In[i].is_open())
        {
            fileArray_In[i].close();
        }
    }
    count_Out = 0u;
}
void Parser::CloseAllFileOut()
{
    for (unsigned i = 0u; i < length_Out; i++)
    {
        if (fileArray_Out[i].is_open())
        {
            fileArray_Out[i].close();
        }
    }
    count_Out = 0u;
}

Parser::~Parser()
{
    CloseAllFileIn();
    CloseAllFileOut();
    length_In = 0u;
    length_Out = 0u;
    if (fileArray_In != NULL)
    {
        delete[] fileArray_In;
        fileArray_In = NULL;
    }
    if (fileArray_Out != NULL)
    {
        delete[] fileArray_Out;
        fileArray_Out = NULL;
    }
}