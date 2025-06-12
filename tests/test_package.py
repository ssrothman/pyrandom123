from __future__ import annotations

import importlib.metadata

import pyrandom123 as m


def test_version():
    assert importlib.metadata.version("pyrandom123") == m.__version__
