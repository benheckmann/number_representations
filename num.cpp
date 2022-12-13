#include <iostream>
#include <array>

std::array<std::string, 5> HELP_COMMANDS = {{"help", "-h", "--help", "-?"}};

void print_help(char **argv)
{
    std::cout << "Usage: " << argv[0] << " <input>" << std::endl;
    std::cout << "Where <input> is one of the following:" << std::endl;
    std::cout << "  > integer" << std::endl;
    std::cout << "  > hexadecimal prefix with 0x" << std::endl;
    std::cout << "  > binary prefix with 0b" << std::endl;
    std::cout << "  > octal prefix with 0" << std::endl;
    std::cout << "  > ASCII character prefixed with c" << std::endl;
}

int parse_input_to_int(std::string input)
{
    int result;
    int base;
    if (input[0] == 'c')
    {
        if (input.size() != 2)
        {
            throw std::invalid_argument("ASCII character must be one character");
        }
        return input[1];
    }
    else if (input.length() > 2 && input[0] == '0' && input[1] == 'x')
    {
        base = 16;
        input = input.substr(2);
    }
    else if (input.length() > 2 && input[0] == '0' && input[1] == 'b')
    {
        base = 2;
        input = input.substr(2);
    }
    else if (input.length() > 1 && input[0] == '0')
    {
        base = 8;
        input = input.substr(1);
    }
    else
    {
        base = 10;
    }
    try
    {
        result = std::stoi(input, nullptr, base);
    }
    catch (std::invalid_argument &e)
    {
        throw std::invalid_argument("Invalid input: " + input);
    }
    return result;
}

void print_representations(int input)
{
    std::cout << "DEC:  " << input << std::endl;
    std::cout << "HEX:  " << std::hex << input << std::endl;
    std::cout << "BIN:  ";
    for (int i = 3; i >= 0; i--)
    {
        std::cout << std::bitset<8>(input >> i * 8) << (i != 0 ? "\'" : "\n");
    }
    std::cout << "OCT:  " << std::oct << input << std::endl;
    std::cout << "CHAR: " << static_cast<char>(input) << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        print_help(argv);
        return 1;
    }
    std::string input(argv[1]);
    if (std::find(HELP_COMMANDS.begin(), HELP_COMMANDS.end(), input) != HELP_COMMANDS.end())
    {
        print_help(argv);
        return 0;
    }
    int int_input;
    try
    {
        int_input = parse_input_to_int(input);
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    print_representations(int_input);
    return 0;
}