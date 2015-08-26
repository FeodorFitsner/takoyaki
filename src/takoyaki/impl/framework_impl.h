// Copyright(c) 2015 kittikun
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include "../public/definitions.h"

namespace Takoyaki
{
    struct FrameworkDesc;
    class DX12Device;
    class IO;
    class ShaderManager;

    class FrameworkImpl
    {
        FrameworkImpl(const FrameworkImpl&) = delete;
        FrameworkImpl& operator=(const FrameworkImpl&) = delete;
        FrameworkImpl(FrameworkImpl&&) = delete;
        FrameworkImpl& operator=(FrameworkImpl&&) = delete;

    public:
        FrameworkImpl();
         ~FrameworkImpl();

        void initialize(const FrameworkDesc&);
        void setProperty(EPropertyID, const boost::any&);
        void present();
        void terminate();
        void validateDevice() const;

        void loadAsyncFileResult(const std::wstring&, const std::vector<uint8_t>&);

    private:
        std::shared_ptr<DX12Device> device_;
        std::shared_ptr<IO> io_;
        std::unique_ptr<ShaderManager> shaderManager_;
    };

} // namespace Takoyaki

