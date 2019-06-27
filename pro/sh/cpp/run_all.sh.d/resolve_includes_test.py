#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import unittest
import resolve_includes


class TestResolveIncludes(unittest.TestCase):
    """test class of resolve_includes.py
    """

    def test_matcher_search(self):
        """test method for matcher
        """
        sentence1 = r'#include "Template.hpp"'
        sentence2 = r'#  include " Template.hpp  "'
        sentence3 = r'#     include"x/a_b.hpp"'
        self.assertIsNotNone(resolve_includes.matcher.search(sentence1))
        self.assertIsNotNone(resolve_includes.matcher.search(sentence2))
        self.assertIsNotNone(resolve_includes.matcher.search(sentence3))

    def test_is_include_line(self):
        """test method for is_include_line
        """
        sentence1 = r'#include "Template.hpp"'
        sentence2 = r'#  include " Template.hpp  "'
        sentence3 = r'#     include"x/a_b.hpp"'
        self.assertTrue(resolve_includes.is_include_line(sentence1))
        self.assertTrue(resolve_includes.is_include_line(sentence2))
        self.assertTrue(resolve_includes.is_include_line(sentence3))

    def test_get_library(self):
        """test method for is_test_get_library
        """
        resolve_includes.lib_path = "/hoge/foo/fuga/"

        sentence1 = r'#include "Template.hpp"'
        sentence2 = r'#    include "Template.hpp"'
        sentence3 = r'#     include"x/a_b.hpp"'
        self.assertEqual(resolve_includes.get_library(
            sentence1), "/hoge/foo/fuga/Template.hpp")
        self.assertTrue(resolve_includes.get_library(
            sentence2), "/hoge/foo/fuga/Template.hpp")
        self.assertTrue(resolve_includes.get_library(
            sentence3), "/hoge/foo/fuga/x/a_b.hpp")


if __name__ == "__main__":
    unittest.main()
