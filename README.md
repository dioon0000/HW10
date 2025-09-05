# 🛠️언리얼 모듈과 플러그인 제작

## 🛠️모듈 제작
`Source 폴더` -> 새폴더 `"Test"`

`Test` > 새 .txt 파일 `“Test.Build.cs”`

`Test` > 새 .txt 파일 `“Test.h”, “Test.cpp”`

```cpp
// Test.Build.cs

using UnrealBuildTool;

public class Test : ModuleRules
{
	public Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{
				// Initial Modules
				"Core", "CoreUObject", "Engine", "InputCore",
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[] { });

	}
}
```
```cpp
// Test.h

#pragma once
```
```cpp
// Test.cpp

#include "Test.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE( FDefaultModuleImpl, Test );
	// Test 모듈은 ModuleAndPlugin 프라이머리게임모듈과는 다름. 일반 모듈임.
```
## 🛠️모듈 연결하기
- 새로운 모듈을 추가하였다면 Visual Studio에서 새 모듈이 함께 빌드되도록 `ModuleAndPlugin.Target.cs` 파일과 `ModuleAndPluginEditor.Target.cs` 파일을 수정
```cpp
// ModuleAndPlugin.Target.cs

using UnrealBuildTool;
using System.Collections.Generic;

public class ModuleAndPluginTarget : TargetRules
{
	public ModuleAndPluginTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("ModuleAndPlugin");
		ExtraModuleNames.Add("Test");
	}
}
```
```cpp
// ModuleAndPluginEditor.Target.cs

using UnrealBuildTool;
using System.Collections.Generic;

public class ModuleAndPluginEditorTarget : TargetRules
{
	public ModuleAndPluginEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("ModuleAndPlugin");
		ExtraModuleNames.Add("Test");
	}
}
```
- 언리얼 에디터가 새로운 .dll 파일도 로딩하도록 `.uproject` 파일도 수정
```cpp
// ModuleAndPlugin.uproject

{
	...
	"Modules": [
		{
			"Name": "Test",
			"Type": "Runtime",
			"LoadingPhase": "PreDefault",
			"AdditionalDependencies": [
				"Engine"
			]
		},
		{
			"Name": "ModuleAndPlugin",
			"Type": "Runtime",
			"LoadingPhase": "Default",
			"AdditionalDependencies": [
				"Engine",
				"Test"
			]
		}
	],
	"Plugins": [
		...
	]
}
```

## 🛠️플러그인 만들기
프로젝트 폴더 > 새 폴더 `“Plugins”`

`Plugins` > 새 폴더 `“Temporary”`

`Temporary` > 새 폴더 `"Content”`, `“Source”` 새 .txt 파일 `“Temporary.uplugin”`

`Source` > 새 폴더 `“Temporary”`

`Source` > 새 .txt 파일 `“Temporary.Build.cs”`

`Source` > 새 .txt 파일 `“Temporary.h”`, `“Temporary.cpp”`

```cpp
// Temporary.uplugin <- 이건 지워야함.

{
	"FileVersion": 3,
	"Version": 1,
	"VersionName": "1.0",
	"FriendlyName": "Temporary",
	"Description": "",
	"Category": "Other",
	"CreatedBy": "",
	"CreatedByURL": "",
	"DocsURL": "",
	"MarketplaceURL": "",
	"SupportURL": "",
	"CanContainContent": true,
	"IsBetaVersion": false,
	"IsExperimentalVersion": false,
	"Installed": false,
	"Modules": [
		{
			"Name": "Temporary",
			"Type": "Runtime",
			"LoadingPhase": "Default"
		}
	]
}
```

```cpp
// Temporary.Build.cs

using UnrealBuildTool;

public class Temporary : ModuleRules
{
	public Temporary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
```

```cpp
// Temporary.h

#pragma once

#include "Modules/ModuleManager.h"

class FTemporaryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
```

```cpp
// Temporary.cpp

#include "Temporary.h"

#define LOCTEXT_NAMESPACE "FTemporaryModule"

void FTemporaryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTemporaryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTemporaryModule, Temporary)
```

## 🛠️플러그인 연결하기
- Temporary 플러그인 속 Temporary 모듈의 빌드 등록
```cpp
// ModuleAndPlugin.Target.cs

...

public class ModuleAndPluginTarget : TargetRules
{
	public ModuleAndPluginTarget(TargetInfo Target) : base(Target)
	{
		...
		ExtraModuleNames.Add("Temporary");
	}
}
```

```cpp
// ModuleAndPluginEditor.Target.cs

...

public class ModuleAndPluginEditorTarget : TargetRules
{
	public ModuleAndPluginEditorTarget(TargetInfo Target) : base(Target)
	{
		...
		ExtraModuleNames.Add("Temporary");
	}
}
```

```cpp
// ModuleAndPlugin.uproject

{
	...,
	"Modules": [
		...,
		{
			"Name": "ModuleAndPlugin",
			"Type": "Runtime",
			"LoadingPhase": "Default",
			"AdditionalDependencies": [
				...,
				"Temporary"
			]
		}
	],
	"Plugins": [
		{
			...
		},  
		{
			"Name": "Temporary",
			"Enabled": true
		}
	]
}
```
