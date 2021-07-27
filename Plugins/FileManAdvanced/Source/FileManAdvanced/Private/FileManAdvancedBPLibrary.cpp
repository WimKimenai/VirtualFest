// Copyright (c) Aaron Hunt 2020

#include "FileManAdvancedBPLibrary.h"
#include "FileManAdvanced.h"
#include "HAL/FileManagerGeneric.h"
#include "ImageUtils.h"
#include "Engine/Texture2D.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"

bool UFileManAdvancedBPLibrary::DeleteFile(FString FileName) {
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.FileExists(*FileName))
		return FFileManagerGeneric::Get().Delete(*FileName);
	else
		return false;
}

bool UFileManAdvancedBPLibrary::GetFilesInPath(TArray<FString>& Files, FString Path, bool SearchSubfolders) {

	FPaths::NormalizeDirectoryName(Path);

	IFileManager& FileManager = IFileManager::Get();

	FString FindFilePath = Path + "/*.*";
	FString Extension = "*.*";

	if (SearchSubfolders)
		FileManager.FindFilesRecursive(Files, (*Path), *Extension, true, false);
	else
		FileManager.FindFiles(Files, (*FindFilePath), true, false);

	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (platformFile.DirectoryExists(*Path))
		return 1;
	else
		return 0;
}

bool UFileManAdvancedBPLibrary::ReadFile(FString FileName, FString & Content) {
	return FFileHelper::LoadFileToString(Content, *(FileName));
}

bool UFileManAdvancedBPLibrary::WriteFile(FString Content, FString FileName) {
	return FFileHelper::SaveStringToFile(Content, *(FileName));
}

static TSharedPtr<IImageWrapper> FromExtension(const FString InImagePath)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	if (InImagePath.EndsWith(".jpg") || InImagePath.EndsWith(".jpeg"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
	}
	else if (InImagePath.EndsWith(".png"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	}
	else if (InImagePath.EndsWith(".bmp"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);
	}
	else if (InImagePath.EndsWith(".ico"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICO);
	}
	else if (InImagePath.EndsWith(".exr"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::EXR);
	}
	else if (InImagePath.EndsWith(".icns"))
	{
		return ImageWrapperModule.CreateImageWrapper(EImageFormat::ICNS);
	}

	return nullptr;
}

UTexture2D* UFileManAdvancedBPLibrary::LoadTextureFromFile(const FString& FileName){
	UTexture2D* Texture = nullptr;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FileName))
	{
		return nullptr;
	}

	TArray<uint8> CompressedData;
	if (!FFileHelper::LoadFileToArray(CompressedData, *FileName))
	{
		return nullptr;
	}

	TSharedPtr<IImageWrapper> ImageWrapper = FromExtension(FileName);

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(CompressedData.GetData(), CompressedData.Num()))
	{
		TArray<uint8> UncompressedRGBA;

		if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
		{
			Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_R8G8B8A8);

			if (Texture != nullptr)
			{

				void* TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
				Texture->PlatformData->Mips[0].BulkData.Unlock();
				Texture->UpdateResource();
			}
		}
	}

	return Texture;
}

FString UFileManAdvancedBPLibrary::GetMainDirectory() {
	return FPaths::ProjectDir();
}

FString UFileManAdvancedBPLibrary::GetLaunchDirectory() {
	return FPaths::LaunchDir();
}

FString UFileManAdvancedBPLibrary::GetEngineDirectory() {
	return FPaths::EngineDir();
}

bool UFileManAdvancedBPLibrary::CreateDirectory(FString FolderName) {
	return IFileManager::Get().MakeDirectory(*FolderName);
}

bool UFileManAdvancedBPLibrary::DeleteDirectory(FString FolderName) {
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.DirectoryExists(*FolderName))
		return FFileManagerGeneric::Get().DeleteDirectory(*FolderName, true, true);
	else
		return false;
}

FDateTime UFileManAdvancedBPLibrary::LastModifiedTime(FString FileName) {
	return IFileManager::Get().GetTimeStamp(*FileName);
}