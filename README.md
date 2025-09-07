<p align="center">
  <img src="https://i.imgur.com/IlxefAY.png" width="150" alt="Minitalk Badge With Bonus">
</p>

<div align="center">

[![42 School](https://img.shields.io/badge/Paris-blue?logo=42&logoColor=fff)](https://42.fr/en/homepage/)
[![Bonus](https://img.shields.io/badge/✔️_Bonus-5cb85c)](https://github.com/baderelg/Minitalk) \
<img src="https://i.imgur.com/HTci8UV.png" width="100" alt="Validation confirmation on the 42 Intra @baelgadi - Sep 1st 2025"> \
[![Validation date](https://img.shields.io/date/1756735200?label=&style=for-the-badge&color=5cb85c)](https://github.com/baderelg/Minitalk)

</div>

> [!NOTE]
> <details>
> <summary><strong>What is 42?</strong></summary>
>
> > [42 School](https://42.fr/en/homepage/) is a coding school focused on peer to peer learning and being project driven. \
> > We are given a project, a set of rules and clear objectives, and then it's up to us to figure out how to achieve the goal. \
> > It pushes to learn how to learn. It may be intense and sometimes frustrating but the sense of accomplishment makes everything worth it. \
> > Short term comfort is thus sacrificed for long term growth and versatility.
> </details>
>
> <details>
> <summary><strong>What is Minitalk?</strong></summary>
>
> > Minitalk is a communication program where 2 programs (server and client) must communicate using only UNIX signals.\
> > The client sends each character, bit by bit via `SIGUSR1` or `SIGUSR2` and the server reconstructs the message.\
> > This project is a deep dive into process communication and signal handling.\
> > Bonus requires including acknowledgment and support for Unicode characters.
> </details>
>
> To make the journey entertaining, I chose to approach the project through the eyes and voice of a fictional character.
>
> <details>
> <summary><strong>Why ?</strong></summary>
>
> > Embodying a character while tackling a project isn't just entertaining, it forges stronger connections with the logic and makes it way more engaging.</br>
> > When you try expressing what you just learned with the voice of a fictional character, it helps cementing the newly acquired knowledge and even adds new perspectives.</br>
> >
> </details>
> <details>
> <summary><strong>Why Varys?</strong></summary>
>
> > Minitalk is about information and whispering secrets between processes.\
> > Varys, as the master of whispers, listens with his network of "little birds" and conveys messages across dangerous places.\
> > The spider shall weave the web of bits and bytes.
> </details>

---

<p align="center">
  <img src="https://i.imgur.com/nKTRpNr.png" alt="And I keep on paddling">
</p>

> “One signal can carry more weight than a thousand ravens."

Greetings. I wanted to personally welcome you into my web to learn how to speak the language of power, and how to send messages through the silence.\
This is **Minitalk**, and I shall be your guide.

# 🕷️ The anatomy of a whisper

My lord / lady, before we move on, may I illuminate key concepts on the subtle art of inter-process communication?

## 🐤 The little birds - The signals

Imagine the realm (every task running on the machine) as lords and ladies going about their daily business. A signal is a simple tap on the shoulder. A non verbal command that interrupts whatever the recipient is doing.\
One tap might mean "The king wishes to see you", while another might mean "Flee. Danger".
It is a way for one process to alert another without engaging in a lengthy conversation.

So, Imagine each signal as one of my little birds carrying **a precise message** through hidden paths.

For this implementation however, I am not granted the full roster, as I am restricted to only two signals : `SIGUSR1` and `SIGUSR2`.\
I chose to interpret them as `0` and `1` respectively. But do as you wish.\
Consider each one as a bit: one note by itself means very little. But 8 in a row? That's a character.\
We are speaking in a secret binary language, understood only by the birds who sing it and by the ear which was trained to listen.

## 📜 The language of secrets - Bitwise operations

> Influence grows like a weed. And so does information.

The secret must be deconstructed. This is where the true art lies: taking a single character and breaking it down into its eight fundamental parts (the bits).

### ➢ Right shift (`>>`): Isolate and read

Consider the character 'A' which in binary tongue is `01000001`.\
To inspect its second bit from the left (~~0~~ `1` ~~000001~~), you shift the entire line 6 places to the right:
```haskell
'A' >> 6 = 00000001
```
You are padding with `0`s from the left, keeping only the `01`~~000001~~ part.

The bit you want to interrogate is now alone in the rightmost position: It's the **least significant bit** (LSB).\
So, by shifting a value to the right, you can inspect every bit it contains.

### ➢ Left shift (`<<`): Assemble

Here, you begin with an empty chamber: `00000000`.\
When a bit arrives, you'll have to place it. But when the second bit arrives, where does it go?\
Picture this: If you shift one step to the left, that creates a vacant space at the end.
```java
Current value			00000001
Shift to the left by 1		00000010
New bit (1) arrives 		00000011
                                       ^
```
Each left shift makes room for a new piece of intelligence, slowly but surely building a complete picture from nothing.\
A mummer's trick.

### ➢ Bitwise OR (`|`)

But how does one place the newly received bit after making room?\
One must use the **Bitwise OR** operator.\
It follows a simple rule: If a bit is `1` in either of the values, the resulting bit is `1`.

<ins>Let us assemble the 'A' (`01000001`) from arriving bits:</ins>

1. Start with `00000000`. `0` arrives first.
```c
result = (00000000 << 1) | 0; // 00000000
```
2. Now you have `00000000` and `1` arrives.
```c
result = (00000000 << 1) | 1; // 00000001
```
3. Value is `00000001` and `0` arrives.
```c
result = (00000001 << 1) | 0; // 00000010
```
*And so on until...*\
Value is now `01000000` and the last bit (`1`) arrives.
```c
result = (01000000 << 1) | 1; // 01000001 = 'A'
```

### ➢ Bitwise AND (`&`)

And how does one, after isolating the bit with a right shift, determine if it is a `1` or a `0`?

As I said. After shifting, the bit we want is the LSB, so at the rightmost position.\
The trick here is to apply a mask of `1` (basically `00000001`) and use the strict AND operator.\
**Only if a bit is 1 in both values, will the result be `1`.**

> [!TIP]
> Position of bits go from 7 to 0.\
> <ins>Position:</ins>  7 6 5 4 3 2 1 0\
> <ins> Binary `A`</ins>: 0 1 0 0 0 0 0 1\
> So the second bit to the left is actually the 6th.

<ins>Let us re-inspect the bit at the 6th position of 'A' (`01000001`):</ins>

1. Isolate the bit (`'A' >> 6`) to get `00000001`
2. Now that you have `00000001`, apply the mask
```c
	00000001	(The isolated bit)
&	00000001	(The mask of 1)
----------
	00000001	(The result is 1 because both are 1)
```

<ins>To make it clearer, how about the bit at the 5th position of 'A' (`01000001`):</ins>

1. Isolate the bit (`'A' >> 5`) to get `00000010`
2. Now that you have `00000010`, apply the mask
```c
	00000010	(The isolated bit)
&	00000001	(The mask of 1)
----------
	00000000	(The result is 0)
```

## 🚩 The destination - PID (Process ID)

Every process within the UNIX realm has a unique identifier: the PID.\
This can be considered as an address to a hidden chamber where my birds must deliver their whispers.\
Now, to ensure that the message finds its target, the little bird (client) must know the recipient's (server's) PID.
That's why the Minitalk Subject requires the server to display its PID at launch.

> [!TIP]
> You can also get the pid by typing `pgrep server`.

## ↕️ The silent nod - Acknowledgement

Communication relies heavily on acknowledgements. These are confirmations that each signal has been received.\
The recipient must acknowledge each received bit, guiding the client to continue with its next transmission.\
Without these acknowledgements, the whispers could be lost to the winds and chaos, the gaping pit, will ensue.

> [!Important]
> For the bonus part, the recipient (server) must acknowledge the received message by sending a signal too.

## 🔠 BONUS PART - Understanding unicode

Secrets do not always arrive in the common tongue. Sometimes, they stem from other parts of the world and they are more complex than a simple `A` or `B`.\
Welcome to the realm of Unicode.

Take other alphabets or emojis for example, they can't be printed using only ASCII. So how does our web handle this?\
With simple elegance: since our birds are trained to carry characters bit by bit, there is nothing more to it.\
They don't need to understands the message, only deliver it. And the terminal shall understand them.

<ins>But if you wish to go further, here is a quick explanation of how it works:</ins>

The genius of this tongue (especially the UTF-8 encoding) lies in its efficiency. It does not waste space.
- A character from the common tongue (like `v`) is a **single-byte** message, and its first bit is always 0. (say `0xxxxxxx`)
- A more complex symbol like `€` is a **two-byte** message. The first byte being the key, as it begins with `110`: `110xxxxx 10xxxxxx`.
- An even more intricate character like those from Yi Ti `字` would take three bytes of space, with the first byte beginning in `1110`: `1110xxxx 10xxxxxx 10xxxxxx`
- And the rarest of symbols, like emojis (`👋`) require four bytes of space. The first byte begins with `11110`: `11110xxx 10xxxxxx 10xxxxxx 10xxxxxx`

When the terminal sees any of the keys, it knows exactly how many bytes it needs to show the actual character.\
So while, conventionally a char is 8 bits. An emoji would actually take 4*8 = 32bits of space.

# 🕷️ The art of whispers

Minitalk is a dance between two programs, working in concert:
- The **server**, sitting in shadow and listening through the mush of signals
- The **client**, sending the message

They both exchange whispers of information, bit by bit through the shadows of the realm.

## 🕸️ Weaving the web – Code architecture

Every good spymaster must spin his web properly.

- **`minitalk.h`**\
Includes necessary tools.\
For this project, [Libft](https://github.com/baderelg/Libft)[^1] is allowed (with [ft_printf](https://github.com/baderelg/Ft_printf)[^2] too).

- **`server.c`**\
The server is the spider, sitting and listening. It doesn't act; it reacts.\
Armed with two signal handlers, one for `SIGUSR1` and one for `SIGUSR2`, it prints the PID so that the client knows where to send its whispers.\
Each signal represents a binary digit (0 or 1). And it must acknowledge reception for every bit to prevent loss by sending `SIGUSR1` to the client.\
Once the server accumulates the necessary **8 bits** to build a single character, it writes it to standard output.\
When a null character (`\0`) is received, it understands that the message is now complete and acknowledges the client by sending `SIGUSR2`.

- **`client.c`**\
It takes exactly 2 arguments (ac = 3): the server’s PID and the message.\
After sending each bit, it waits for acknowledgement (`SIGUSR1`) from the server before proceeding. Once the full string and its terminating char `\0` are sent, the client bows out. For the Bonus part, the final acknowledgement (`SIGUSR2`) from the server is handled by writing on the standard output that the message has been received.

## 🗝️ Secrets to success

> The storms come and go, the waves crash overhead, the big fish eat the little fish, and I keep on paddling.

Here is how you can keep on paddling too.

<table>
  <tr>
    <td width="22%"><b>Signal Safety</b></td>
    <td>You must avoid any danger. Only async-signal-safe functions should be called directly within a signal handler. That means, no <code>ft_printf</code>, but rather <code>write</code>. <br> Search for async-signal-safe functions inside the manual (<code>man 7 signal</code>).</td>
  </tr>
  <tr>
    <td><b>Portability</b></td>
    <td>Use the <code>pid_t</code> type instead of <code>int</code>. There is no guarantee that on other systems the PID wouldn't be a <code>long</code> for example.</td>
  </tr>
  <tr>
    <td><b>Protection</b></td>
    <td>Protect the calls to <code>kill()</code> and <code>sigaction()</code> as they send -1 on error. Handle those cases no matter how rare they could be.</td>
  </tr>
  <tr>
    <td><b>Simultaneous messengers & interrupted ones</b></td>
    <td>Have you thought of what happens when there are multiple messengers at the same time? Or when a message gets interrupted mid-sentence? UNIX signals can not be queued, so unless you handle it, at least try to protect the server. Don't let it crash. <br>I handle this in my function <b>client_sig_handler</b> at the very start, where the client's PID is checked at each step, and if it's different, then everything gets reset.</td>
  </tr>
  <tr>
    <td><b>Bonus</b></td>
    <td>Without acknowledgment, a message would be lost in the chaos. On the client, I use a global variable and make the client wait accordingly between bits. A small <code>usleep()</code> call prevents the little birds from flapping too much (and the CPU from being constantly used).<br> The use of <code>volatile sig_atomic_t</code> ensures that:<br>- <code>volatile</code>: the compiler won't do optimizations and cache out the value of my variable, as I signify that its value may change at any time.<br>- <code>sig_atomic_t</code>: to indicate that the operations should be atomic, meaning that the value should be read or written in a single uninterruptible operation.</td>
  </tr>
</table>

## Running the Program

Open two terminals. In the first, start the server:

```bash
$ ./server
Server PID: 1001

```

In the second, call your client with the server’s PID and your message:

```bash
$ ./client 1001 "A very small process can cast a very large shadow"

```

The server will print the message, one character at a time, as it decodes the bits. As a little bonus, the client will show the binary representation of your message as a courtesy to those who speak this strange language.

# 🕷️ Go further

## Why not use a buffer?

The french version of the subject contains a line that could be misleading: *"Une fois la chaine <ins>entièrement</ins> reçue, le serveur doit l'afficher."*\
This means: Once the string is <ins>completely</ins> received, the server must display it.

Taken literally, this means that one must wait and gather every character in a buffer before printing the message.

However, in the english subject which is the one to consider:\
*"The client must send the specified string to the server. Once received, the server must print it."*\
So this is not specified in the same way.

Were you to gather characters in a buffer, you'd have to use malloc which is **not** an async-signal-safe function.\
Calling `malloc()` inside a signal handler is dangerous because it can interfere with memory allocation operations that were already in progress, leading to corrupted memory.\
It must be avoided at all costs inside a handler.

The critical rule when working with signals is that only a specific list of functions can be safely called from within a signal handler:
```
man 7 signal-safety
```

Of course, if you want to comply at all costs with the french subject, you could use a static buffer, but you'll face two new problems:

- Risk of buffer overflow\
No matter what size you choose, the client could send a string that's longer than the buffer, causing a buffer overflow where you write past the end of your allocated memory.\
There is no "safe" size for a static buffer.

- "Without delay"\
The subject states that the server must display the string **without delay**.\
Using a buffer, the server will not print anything until the entire string is received.\
For long strings, this will introduce a very noticeable delay between the client sending the message and the server actually displaying it.


## A farewell from the spider

These whispers must have prepared you for the task ahead. But remember, my lord /  lady, secrets are currency and currency is power.\
As you craft your very own Minitalk, always think like a spymaster: every bit matters, every signal matters.\
May your little birds' whispers serve you well.

<hr>
<p align="center">
<sub><i>MINITALK badge © @Cadets for Cadets — used under MIT License.</i></sub>
<br>
<sub><a href="https://github.com/ayogun/42-project-badges/blob/main/LICENSE">See full license here</a></sub>
</p>

[^1]: Libft is the first project of the common core at 42. [My version explained by Ted Lasso is right here!](https://github.com/baderelg/Libft/)
[^2]: Ft_printf is another project of the common core at 42. [My version explained by Donquixote Doflamingo is right here!](https://github.com/baderelg/Ft_printf)
