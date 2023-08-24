import unittest
from credit_card import validate

class TestCreditCardValidator(unittest.TestCase):
    """
    Tests a credit card number validator
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

if __name__ == '__main__':
    unittest.main(argv=['unittest','TestCreditCardValidator'], verbosity=2, exit=False)