Pod::Spec.new do |spec|
	spec.name = "swirl-sdk-ios"
	spec.version = "3.6.1"
	spec.summary = "Swirl Proximity Framework"
	spec.homepage = "https://swirlnetworks.github.com/swirl-sdk-ios"
	spec.license = { type: "MIT", file: "LICENSE.md" }
	spec.authors = { "Swirl Networks, Inc." => "tom@swirl.com" }
	spec.social_media_url = "http://twitter.com/swirl"
	
	spec.platform = :ios, "9.0"
	spec.requires_arc = true
	spec.source = { git: "https://github.com/swirlnetworks/swirl-sdk-ios.git", tag: "#{spec.version}", submodules: true }
	spec.vendored_frameworks = "framework/Swirl.framework"
end
