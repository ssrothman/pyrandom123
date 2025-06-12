"""
Copyright (c) 2025 Simon Rothman. All rights reserved.

pyrandom123: Python bindings for the random123 library of counter-based random number generators
"""

from __future__ import annotations

from ._version import version as __version__
from ._core import add, subtract

__all__ = ["__version__", "add", "subtract"]
