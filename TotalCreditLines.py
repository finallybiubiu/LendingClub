"""
Created on May 30, 2013

@author: gczajkow
"""

import Filter
import LoanEnum

DEFAULT_TOTAL_ACCOUNTS = 0


class TotalCreditLines(Filter.Filter):
    """
    classdocs
    """
    def __init__(self, args, current=None):
        """
        Constructor
        """
        options = [10, 20, 30]

        Filter.Filter.__init__(self, args, options, current)

    def convert(self, raw_data):
        return int(raw_data) if raw_data else DEFAULT_TOTAL_ACCOUNTS

    def apply(self, loan, total_acc=LoanEnum.LOAN_ENUM_total_acc):
        return loan[total_acc] <= self.get_current()
