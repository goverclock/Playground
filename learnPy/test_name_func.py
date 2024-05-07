#!env python3
import unittest
from name_func import get_formatted_name

class NameTestCase(unittest.TestCase):
    """testing the function"""
    def test_first_last_name(self):
        formatted = get_formatted_name('hello', 'hell')
        self.assertEqual(formatted, 'Hello Hell')

if __name__ == '__main__':
    unittest.main()

