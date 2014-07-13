"""
Created on May 30, 2013

@author: gczajkow
"""

import Filter
import LoanEnum

DEFAULT_MTHS_SINCE_LAST_DELINQ = 61

class MonthsSinceLastDelinquency(Filter.Filter):
    """
    classdocs
    """
    def __init__(self, args, current=None):
        """
        Constructor
        """
        options = [12, 24, 60]

        Filter.Filter.__init__(self, args, options, current)

    def convert(self, raw_data):
        return int(raw_data) if raw_data else DEFAULT_MTHS_SINCE_LAST_DELINQ

    def apply(self, loan, mths_since_last_delinq=LoanEnum.LOAN_ENUM_mths_since_last_delinq):
        return loan[mths_since_last_delinq] >= self.get_current()
