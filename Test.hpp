/*
 * the file would look something like that:
 * --first group--
 * 1 first_units[0] = times[0] second_units[0]
 * 1 second_units[0](=second_units[0]) = times[1] second_units[1]
 * ...
 * 1 second_units[(actual_size/2)-1](=second_units(actual_size/2)-1) = times[(actual_size/2)] second_units[(actual_size/2)-1]
 * --second group--
 * 1 second_units[(actual_size/2)] = times[(actual_size/2)] second_units[(actual_size/2)]
 * 1 second_units[(actual_size/2)](=second_units[(actual_size/2)]) = times[(actual_size/2)] second_units[(actual_size/2)]
 * ...
 * 1 second_units[actual_size-1](=second_units[actual_size-2]) = times[actual_size] second_units[actual_size]
 */

namespace ariel {
    class Test {
        int i = 0; //to keep track on filling up the arrays

        std::string rand_unit();

        std::string write_unit(std::ofstream &file);

        double write_num(std::ofstream &file);

        void write_first_line(std::ofstream &file);

        void write_line(std::ofstream &file);

    public:
        std::string first_units[10];
        std::string second_units[10];
        double times[10];
        int actual_size;
        void rand_file();
        std::string flip_letters(std::string str);


    };
}