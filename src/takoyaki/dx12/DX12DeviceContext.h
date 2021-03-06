// Copyright(c) 2015 kittikun
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub license, and / or sell
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

#include <d3d12.h>
#include <memory>

#include "DX12ConstantBuffer.h"
#include "DX12Device.h"
#include "DX12DescriptorHeap.h"
#include "DX12Texture.h"

#include "../rwlock_map.h"
#include "../thread_safe_stack.h"

namespace Takoyaki
{
    // TODO: Not thread safe, implement some protection later
    class DX12DeviceContext : public std::enable_shared_from_this<DX12DeviceContext>
    {
        DX12DeviceContext(const DX12DeviceContext&) = delete;
        DX12DeviceContext& operator=(const DX12DeviceContext&) = delete;
        DX12DeviceContext(DX12DeviceContext&&) = delete;
        DX12DeviceContext& operator=(DX12DeviceContext&&) = delete;

    public:
        DX12DeviceContext(std::weak_ptr<DX12Device>);

        DX12DescriptorHeapCollection<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>& getRTVDescHeapCollection() { return descHeapRTV_; }
        DX12DescriptorHeapCollection<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>& getSRVDescHeapCollection() { return descHeapSRV_; }

        DX12ConstantBuffer& CreateConstanBuffer(const std::string&);
        DX12Texture& CreateTexture();

    private:
        std::weak_ptr<DX12Device> owner_;
        DX12DescriptorHeapCollection<D3D12_DESCRIPTOR_HEAP_TYPE_RTV> descHeapRTV_;
        DX12DescriptorHeapCollection<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV> descHeapSRV_;

        RWLockMap<std::string, DX12ConstantBuffer> constantBuffers_;
        ThreadSafeStack<DX12Texture> textures_;
    };
} // namespace Takoyaki