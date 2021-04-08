#pragma once

struct PlatformConfig;

class LibBuilder {
public:
	LibBuilder(const PlatformConfig *config) : m_config(config) {}

	void run();

private:
	PlatformConfig *m_config;
};