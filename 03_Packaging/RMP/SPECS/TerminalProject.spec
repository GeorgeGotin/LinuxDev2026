Name:           TerminalProject
Version:        0.0.1
Release:        alt1
Group:          Other
License:        BSD
URL:            https://github.com/GeorgeGotin/LinuxDev2026/tree/main/01_TerminalProject
Source:         %name-%version.tar.gz
Summary:        something

BuildRequires:  libncursesw-devel


%description
Show file in window

%prep
%setup

%build
make

%install
make DESTDIR=%buildroot%_bindir/%name install

%files
%_bindir/%name