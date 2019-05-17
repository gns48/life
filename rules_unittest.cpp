#include "life.hpp"

int main(int ac, char **av) {
    RuleInterface<cell_unit_t> *rules = new ConwayRule<cell_unit_t>;
    delete rules;
    return 0;
}
