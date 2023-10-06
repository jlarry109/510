import max_seq
import unittest

class TestMaxSubseq(unittest.TestCase):
    
    def test_maxAtEnd(self):
        assert(max_seq.max_seq([-1, 1, 1, 3, 5, 8, 2, 4, 6, 9, 10]) == [2, 4, 6, 9, 10])
    def test_maxStartAtMiddle(self):
        assert(max_seq.max_seq([50,40,30,1,2,3,4,5]) == [1,2,3,4,5])
    
    def test_MaxAtBeginning(self):
        assert(max_seq.max_seq([1,2,3,4,5,50,40,30]) == [1,2,3,4,5,50])
    
    def test_others(self):
        print(max_seq.max_seq("50,40,30,1,2,3,4,5"))
        print(max_seq.max_seq(["ab"]))
    
unittest.main(argv=['TestMaxSubseq'],
              verbosity=2, exit=False)