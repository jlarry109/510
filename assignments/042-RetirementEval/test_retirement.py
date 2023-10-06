# month > 12
    # negative month and negative year
    # A valid percentage rate value must not be over 100%?
    # Should we validate data each month or can we validate for every month in the file before we start?
# python3 retirement.py sp_data.csv bond_data.csv 1971.12 2017.12
import unittest
from credit_card import validate

class TestRetirementClass(unittest.TestCase):
    """
    Tests the retirement investment 
    """

    def test_valid_visa(self):
        """Ensures a valid visa number passes"""
        self.assertTrue(validate("4263982640269299"))

    def test_valid_mastercard(self):
        """Ensures a valid mastercard number passes"""
        self.assertTrue(validate("5425233430109903"))        

    def test_valid_american_express(self):
        """Ensures a valid american express number passes"""
        self.assertTrue(validate("374245455400126")) 

    def test_invalid_american_express(self):
        """Ensure an invalid american express number fails"""
        self.assertFalse(validate("377024907644532"))                   

    def test_invalid_length_below_visa(self):
        self.assertFalse(validate("426398264026299"))
        
    def test_invalid_length_below_mastercard(self):
        self.assertFalse(validate("542523340109903"))
        
    def test_invalid_length_below_american_express(self):
        self.assertFalse(validate("374245455401269"))
        
    def test_invalid_length_above_visa(self):
        self.assertFalse(validate("42639826402629911"))
        
    def test_invalid_length_above_mastercard(self):
        self.assertFalse(validate("54252334010990311"))
        
    def test_invalid_length_above_american_express(self):
        self.assertFalse(validate("3742454554012612"))
        
    def test_invalid_character_at_last_position(self):
        self.assertFalse(validate("377024907644535a"))
    
    def test_invalid_character_at_first_position(self):
        self.assertFalse(validate("a377024907644537"))
        
    def test_invalid_type_float(self):
        self.assertFalse(validate("542.05233430109903"))
    
    def test_invalid_type_list(self):
        self.assertFalse(validate("42052334301099039"))
    
    def test_invalid_empty_string(self):
        self.assertFalse(validate(""))
        
    def test_invalid_empty_string(self):
        self.assertFalse(validate("5663982640269299"))
if __name__ == '__main__':
    unittest.main(argv=['unittest','TestCreditCardValidator'], verbosity=2, exit=False)