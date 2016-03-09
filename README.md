# ARM9 Launcher
This project aims to launch multiple ARM9 payloads from the home menu in multiple versions as a CIA.

We are capable to do this by doing a code patch with a cfw on the p9 process code that handles pxi service calls to inject a little code that acts as a hook for other payloads. This is fully working with firm version 10.2

So, you require to be running CakesFW to patch the hook on emunand, or run CakesFW with A9LH and patch the hook on sysnand.
If you are on 9.2 or below, patching the hook in sysnand is not advised as you can reach ARM9 by other means.

This software is composed of three parts:
- The firm patch: This is the entry point, where we modify a default jump address in a switch to a defined location.
- The ARM9 Hook: This is the important part, this code handles the invalid command buffer and uses the first translated parameter as an address of a payload to copy to a defined empty ARM9-only memory region. This should be placed at the location pointed by the hook. The hook will jump back where it should on the 3DS firm, returning safely to sandbox.
- The launcher: With the patch and the hook in place, we only need an ARM9 payload embedded into a custom cia to call the system call with the payload there. Altenatively, you could load the payload from the SD. This cia needs pxi:dev access to work. The payload should jump back to the hook, or the system will crash.

Developers be aware: you are running custom code impersonating as process9's pxi:dev. The arm11 cia thread stops, but the home menu is still running below. This is completely intended as a mean of integrating with the 3DS native software. This renders some delicate, hacky things impossible but still allows ARM9 code execution.

What this is:
- A quite straightforward way for developers to deliver ARM9 embedded code packed in a cia to the end user in fw versions >9.2.
- A breach point for full memory access in runtime. (TODO: explore possibilities running a register based code in background)
- An integration effort with 3DS native software.

What this isn't:
- ULTRA XTRA EGGSPLOIT FOR PIRACY STUFF !!!!!!1111!!!!!!!!1!!!!1!!1one! (as it needs a cfw to run, in this case, cakesFW)
- A way to run decrypt9 as a cia. (d0k3 already provided this for <=9.2 systems so go get it!)
