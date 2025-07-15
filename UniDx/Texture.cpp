#include "Texture.h"

#include <filesystem>

#include "D3DManager.h"
#include "Debug.h"


namespace UniDx
{

bool Texture::load(const std::wstring& filePath)
{
	// WIC�摜��ǂݍ���
	auto image = std::make_unique<DirectX::ScratchImage>();
	if (FAILED(DirectX::LoadFromWICFile(filePath.c_str(), DirectX::WIC_FLAGS_NONE, &m_info, *image)))
	{
		// ���s
		m_info = {};
		return false;
	}

	// �~�b�v�}�b�v�̐���
	if (m_info.mipLevels == 1)
	{
		auto mipChain = std::make_unique<DirectX::ScratchImage>();
		if (SUCCEEDED(DirectX::GenerateMipMaps(image->GetImages(), image->GetImageCount(), image->GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, *mipChain)))
		{
			image = std::move(mipChain);
		}
	}

	// ���\�[�X�ƃV�F�[�_�[���\�[�X�r���[���쐬
	if (FAILED(DirectX::CreateShaderResourceView(D3DManager::instance->GetDevice().Get(), image->GetImages(), image->GetImageCount(), m_info, &m_srv)))
	{
		// ���s
		m_info = {};
		return false;
	}

	std::filesystem::path path(filePath);
	fileName = path.filename();

	// �����I
	return true;
}


void Texture::setForRender() const
{
	D3DManager::instance->GetContext()->PSSetShaderResources(0, 1, m_srv.GetAddressOf());
}

}