/*
Created on July 27, 2014

@author:     Gregory Czajkowski

@copyright:  2013 Freedom. All rights reserved.

@license:    Licensed under the Apache License 2.0 http://www.apache.org/licenses/LICENSE-2.0

@contact:    gregczajkowski at yahoo.com
*/

#ifndef __LC_LCBT_HPP__
#define __LC_LCBT_HPP__

#include <vector>
#include <string>
#include "Loan.hpp"
#include "LoanData.hpp"

namespace lc
{

class LCBT
{
public:
    LCBT(const LoanTypeVector& conversion_filters, const int worker_idx) :
        _args(LCArguments::Get()),
        _filters(conversion_filters.size()),
        _test_filters(nullptr),
        _worker_idx(worker_idx),
        _loan_data(conversion_filters, worker_idx)
    {
    }
        
    void initialize() 
    {
        _loan_data.initialize();
    }

    LoanReturn test(FilterPtrVector& test_filters)
    {
        _invested.clear();
        _test_filters = &test_filters;

        for (auto& loan : _loan_data.get_loans()) {
            if (consider(loan)) {
                _invested.push_back(loan.rowid);
            }
        }
        return _loan_data.get_nar(_invested);
    }

    bool consider(const Loan& loan) 
    {
        for (auto& lc_filter : *_test_filters) {
            if (!lc_filter->apply(loan)) {
                return false;
            }
        }
        return true;
    }

    void debug_msg(const LCString& msg) 
    {
        if (_args["verbose"].as<bool>()) {
            std::cout << "Worker[" << _worker_idx << "] " << msg << '\n';
        }
    }
    unsigned total_loans() const 
    {
        return _loan_data.total_loans();
    }

private:
    const Arguments&						_args;
    FilterPtrVector					        _filters;
    FilterPtrVector*                        _test_filters;
    const int								_worker_idx;
    LoanData								_loan_data;
    LoanValueVector                         _invested;
};

};

#endif // __LC_LCBT_HPP__
