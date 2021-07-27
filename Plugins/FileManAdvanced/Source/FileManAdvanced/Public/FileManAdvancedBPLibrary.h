// Copyright (c) Aaron Hunt 2020

#pragma once

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/FileManager.h"
#include "DDSLoader.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileManAdvancedBPLibrary.generated.h"

UCLASS()
class UFileManAdvancedBPLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
		/** Deletes a file. */
		UFUNCTION(BlueprintCallable, Category = "FileManAdvanced|Files")
			static bool DeleteFile(FString FileName);

		/** Gets all files in a folder. If you search subfolders, node returns full paths. */
		UFUNCTION(BlueprintPure, Category = "FileManAdvanced|Directories", meta = (Keywords = "All Files Directory"))
			static bool GetFilesInPath(TArray<FString>& Files, FString Path, bool SearchSubfolders);

		/** Reads a file, then returns its content. */
		UFUNCTION(BlueprintPure, Category = "FileManAdvanced|Files", meta = (Keywords = "Load Get Text"))
			static bool ReadFile(FString FileName, FString & Content);

		/** Writes content to a file. Returns true if success! */
		UFUNCTION(BlueprintCallable, Category = "FileManAdvanced|Files", meta = (Keywords = "Save Set Text"))
			static bool WriteFile(FString Content, FString FileName);

		/** Gets image file, returns a Texture2D object reference. */
		UFUNCTION(BlueprintPure, Category = "FileManAdvanced|Files", meta = (Keywords = "Load Get Image"))
			static UTexture2D* LoadTextureFromFile(const FString& FileName);

		/** Returns the Project Directory. */
		UFUNCTION(BlueprintPure, Category = "FileManAdvanced|Directories", meta = (Keywords = "Load Get Directory"))
			static FString GetMainDirectory();

		/** Returns the directory the application was launched from. */
		UFUNCTION(BlueprintPure, Category = "FileManAdvanced|Directories", meta = (Keywords = "Load Get Directory"))
			static FString GetLaunchDirectory();

		/** Returns the base Engine Directory. */
		UFUNCTION(BlueprintPure, Category = "FileManAdvanced|Directories", meta = (Keywords = "Load Get Directory"))
			static FString GetEngineDirectory();

		/** Creates a new directory at the specified path. */
		UFUNCTION(BlueprintCallable, Category = "FileManAdvanced|Directories", meta = (Keywords = "Make Add New Folder"))
			static bool CreateDirectory(FString FolderName);

		/** Deletes a directory and all files inside. */
		UFUNCTION(BlueprintCallable, Category = "FileManAdvanced|Directories", meta = (Keywords = "Delete Trash Folder"))
			static bool DeleteDirectory(FString FolderName);

		/** Returns a file's "last modified" timestamp. */
		UFUNCTION(BlueprintPure, Category = "FileManAdvanced|Files", meta = (Keywords = "Get Last Modified Time Created"))
			static FDateTime LastModifiedTime(FString FileName);

};