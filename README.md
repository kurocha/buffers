# Buffers

This library provides set of light weight C++ classes for dealing with buffers of data. It tries to encourage memory safety and efficiency where possible.

[![Build Status](https://travis-ci.org/kurocha/buffers.svg?branch=master)](https://travis-ci.org/kurocha/buffers)

## Setup

Firstly the build tool `teapot` needs to be installed (which requires [Ruby][2]):

	$ gem install teapot

To fetch all dependencies, run:

	$ teapot fetch

[2]: http://www.ruby-lang.org/en/downloads/

## Usage

There are three high-level interfaces provided: `Buffer` which represents read-only data, `MutableBuffer` which represents read/write data of fixed size, and `ResizableBuffer` which represents a read/write buffer whose size may change.

The typical use case to bring data into the library is to use `StaticBuffer` which doesn't copy data but simply provides the wrapper around existing data. You can then call a function which expects the `const Buffer &` argument, or alternatively append this data to a `DynamicBuffer` to build up some more complex structure.

Reading and writing binary data from disk quickly is an important use-case and is the responsibiltiy of `File` and `MappedBuffer`. It uses `mmap`, `posix_fallocate` and `memcpy` internally to write data to disk efficiently. It uses `mmap` to load data from disk with no copying involved. It's the most efficient way to deal with data.

Finally, work is being done to integrate `MappedBuffer` with zero-copy networking. This is a work in progress.

## Contributing

1. Fork it.
2. Create your feature branch (`git checkout -b my-new-feature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin my-new-feature`).
5. Create new Pull Request.

## License

Released under the MIT license.

Copyright, 2016, by [Samuel G. D. Williams](http://www.codeotaku.com/samuel-williams).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
