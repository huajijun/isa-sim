#include "sim.h"
Sim::Sim(const cfg_t *cfg, bool halted,
        std::vector<std::pair<reg_t, mem_t*>> mems,
        const std::vector<std::string>& args)
        :Htif(args),
        cfg(cfg),
        mems(mems),
        {

}